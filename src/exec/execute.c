/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/31 12:57:24 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	execute(t_mshell *mshell)
{
	int	i;
	int	std_in;
	int	std_out;

	std_in = dup(0);
	std_out = dup(1);
	i = return_builtin_num(mshell->cmdarr[0].args[0]);
	if (mshell->cmdarr_l == 1 && i != -1)
	{
		heredoc(mshell, 0);
		open_input_files(mshell, 0);
		open_output_files(mshell, 0);
		mshell->builtin[i].fn_ptr(mshell);
		dup2(std_in, 0);
		dup2(std_out, 1);
		close(std_in);
		close(std_out);
	}
	else
		ft_piping(mshell);
}

void	heredoc(t_mshell *mshell, int i)
{
	char	*line;
	char	*limiter;
	int		tmp_fd;
	int		j;

	j = 0;
	while (j < mshell->cmdarr[i].inp_l)
	{
		if (mshell->cmdarr[i].inp[j].type == T_HEREDOC)
		{
			limiter = mshell->cmdarr[i].inp[j].word;
			tmp_fd = open_file("/tmp/heredoc_tmp", 3);
			while (1)
			{
				line = readline("heredoc> ");
				if (!line || ft_strcmp(line, limiter) == 0)
				{
					free(line);
					break ;
				}
				write(tmp_fd, line, ft_strlen(line));
				write(tmp_fd, "\n", 1);
				free(line);
			}
			close(tmp_fd);
		}
		j++;
	}
}

void	open_input_files(t_mshell *mshell, int i)
{
	int	j;
	int	file;

	j = 0;
	while (j < mshell->cmdarr[i].inp_l)
	{
		if (mshell->cmdarr[i].inp[j].type == T_HEREDOC)
			file = open_file("/tmp/heredoc_tmp", 2);
		else
			file = open_file(mshell->cmdarr[i].inp[j].word, 2);
		if (file < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(file, 0);
		close(file);
		j++;
	}
}
void	open_output_files(t_mshell *mshell, int i)
{
	int	j;
	int	file;

	j = 0;
	while (j < mshell->cmdarr[i].out_l)
	{
		if (mshell->cmdarr[i].out[j].type == T_APPEND)
			file = open_file(mshell->cmdarr[i].out[j].word, 0);
		else
			file = open_file(mshell->cmdarr[i].out[j].word, 1);
		if (file < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(file, 1);
		close(file);
		j++;
	}
}

void	ft_piping(t_mshell *mshell)
{
	int		i;
	pid_t	pid;
	int		j;
	int		cmd_count;
	int		pipes[mshell->cmdarr_l - 1][2];

	j = 0;
	i = 0;
	cmd_count = mshell->cmdarr_l;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(pipes[i - 1][0], 0);
			if (i != cmd_count - 1)
				dup2(pipes[i][1], 1);
			j = 0;
			while (j < cmd_count - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			heredoc(mshell, i);
			open_input_files(mshell, i);
			open_output_files(mshell, i);
			mshell->cmd_num = i;
			ft_execute(mshell);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		wait(NULL);
		i++;
	}
}

void	ft_execute(t_mshell *mshell)
{
	int i;

	i = return_builtin_num(mshell->cmdarr[mshell->cmd_num].args[0]);
	if (i == -1)
		ft_execve(mshell);
	else
		mshell->builtin[i].fn_ptr(mshell);
}