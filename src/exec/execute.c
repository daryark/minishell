/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/02 12:04:28 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

// execute_just_pipes() is a function that executes a command with pipes
//  like: ls | wc or ls | grep .c | wc -l | cat -e

void	execute_just_pipes(char **cmds, char **envp)
{
	int	i;
	int	fd[2];
	int	fd_in;

	i = 0;
	while (cmds[i] != NULL)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(fd_in, 0);
			if (cmds[i + 1] != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			ft_execve(cmds[i], envp);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fd_in = fd[0];
		}
		i++;
	}
}

// execute_infile_outfile() is a function that executes a command with input and output redirection
// with pipes like: ls < file.txt | wc > file2.txt or
// < file.txt cat | wc -c | cat -e | wc > file2.txt

void	execute_infile_outfile(t_args args)
{
	int	i;
	int	fd[2];
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 1;
	i = 0;
	if (args.input)
		fd_in = args.infile;
	if (args.output)
		fd_out = args.outfile;
	while (i < args.pipes + 1)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(fd_in, 0);
			if (args.cmds[i + 1] != NULL)
				dup2(fd[1], 1);
			else
				dup2(fd_out, 1);
			close(fd[0]);
			close(fd[1]);
			ft_execve(args.cmds[i], args.envp);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fd_in = fd[0];
		}
		i++;
	}
}
