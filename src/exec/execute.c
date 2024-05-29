/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/29 16:25:33 by btvildia         ###   ########.fr       */
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

void	heredoc(t_mshell *mshell, int i, int j, int fd[2])
{
	char	*line;
	char	*limiter;

	line = NULL;
	limiter = mshell->cmdarr[i].inp[j].word;
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

void	open_output_files(t_mshell *mshell, int i)
{
	int	j;
	int	outfile;

	j = 0;
	while (j < mshell->cmdarr[i].out_l)
	{
		if (mshell->cmdarr[i].out[j].type == T_APPEND)
			outfile = open_file(mshell->cmdarr[i].out[j].word, 0);
		else
			outfile = open_file(mshell->cmdarr[i].out[j].word, 1);
		dup2(outfile, 1);
		close(outfile);
		j++;
	}
}

void	open_input_files(t_mshell *mshell, int i)
{
	int	j;
	int	infile;

	j = 0;
	while (j < mshell->cmdarr[i].inp_l)
	{
		infile = open_file(mshell->cmdarr[i].inp[j].word, 2);
		dup2(infile, 0);
		close(infile);
		j++;
	}
}

void	ft_piping(t_mshell *mshell)
{
	int	i;
	int	fd[2];
	int	j;
	int	infile;
	int	pid;

	j = 0;
	i = 0;
	infile = 0;
	while (i < mshell->cmdarr_l)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			j = 0;
			while (j < mshell->cmdarr[i].inp_l)
			{
				if (mshell->cmdarr[i].inp[j].type == T_HEREDOC)
					heredoc(mshell, i, j, fd);
				j++;
			}
			if (i != 0)
			{
				dup2(infile, 0);
				close(infile);
			}
			if (i != mshell->cmdarr_l - 1)
				dup2(fd[1], 1);
			close(fd[0]);
			open_output_files(mshell, i);
			open_input_files(mshell, i);
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
