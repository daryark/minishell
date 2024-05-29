/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/29 18:19:12 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	execute(t_mshell *mshell)
{
	int	i;

	i = return_builtin_num(mshell->cmdarr[0].args[0]);
	if (mshell->cmdarr_l == 1 && i != -1)
	{
		mshell->cmd_num = 0;
		mshell->builtin[i].fn_ptr(mshell);
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

void	open_files(t_mshell *mshell, int i)
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
	int	i;
	int	fd[2];
	int	infile;
	int	pid;

	i = 0;
	infile = 0;
	while (i < mshell->cmdarr_l)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			heredoc(mshell, i);
			if (i != 0)
			{
				dup2(infile, 0);
				close(infile);
			}
			if (i != mshell->cmdarr_l - 1)
				dup2(fd[1], 1);
			close(fd[0]);
			open_files(mshell, i);
			mshell->cmd_num = i;
			ft_execute(mshell);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			if (i != 0)
				close(infile);
			infile = fd[0];
		}
		i++;
	}
}

void	ft_execute(t_mshell *mshell)
{
	int	i;

	i = return_builtin_num(mshell->cmdarr[mshell->cmd_num].args[0]);
	if (i == -1)
		ft_execve(mshell);
	else
		mshell->builtin[i].fn_ptr(mshell);
}
