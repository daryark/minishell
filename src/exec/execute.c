/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/03 17:28:18 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	execute(t_mshell *mshell)
{
	int	i;
	int	std_in;
	int	std_out;
	int	**pipes;

	pipes = ft_malloc(sizeof(int *) * (mshell->cmdarr_l - 1));
	i = return_builtin_num(mshell->cmdarr[0].args[0]);
	if (mshell->cmdarr_l == 1 && i != -1)
	{
		std_in = dup(0);
		std_out = dup(1);
		heredoc_loop(mshell, 0);
		open_input_files(mshell, 0);
		open_output_files(mshell, 0);
		mshell->builtin[i].fn_ptr(mshell);
		close(std_in);
		close(std_out);
	}
	else
	{
		open_fds(mshell, pipes);
		ft_piping(mshell, pipes);
		close_fds(mshell, pipes);
		wait_in_parent(mshell);
	}
}

void	ft_piping(t_mshell *mshell, int **pipes)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < mshell->cmdarr_l)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(pipes[i - 1][0], 0);
			if (i != mshell->cmdarr_l - 1)
				dup2(pipes[i][1], 1);
			close_fds(mshell, pipes);
			signal(SIGINT, child_signal);
			heredoc_loop(mshell, i);
			open_input_files(mshell, i);
			open_output_files(mshell, i);
			mshell->cmd_num = i;
			signal(SIGINT, SIG_DFL);
			ft_execute(mshell);
			exit(mshell->exit_status);
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
