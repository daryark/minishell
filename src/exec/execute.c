/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/31 16:27:40 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	execute(t_mshell *mshell)
{
	int	i;
	int	std_in;
	int	std_out;
	int	pipes[mshell->cmdarr_l - 1][2];

	std_in = dup(0);
	std_out = dup(1);
	i = return_builtin_num(mshell->cmdarr[0].args[0]);
	if (mshell->cmdarr_l == 1 && i != -1)
	{
		heredoc_loop(mshell, 0);
		open_input_files(mshell, 0);
		open_output_files(mshell, 0);
		mshell->builtin[i].fn_ptr(mshell);
		dup2(std_in, 0);
		dup2(std_out, 1);
		close(std_in);
		close(std_out);
	}
	else
	{
		ft_piping(mshell, pipes);
		close_fds(mshell, pipes);
		wait_in_parent(mshell);
	}
}

void	ft_piping(t_mshell *mshell, int pipes[][2])
{
	int		i;
	pid_t	pid;

	open_fds(mshell, pipes);
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
			heredoc_loop(mshell, i);
			open_input_files(mshell, i);
			open_output_files(mshell, i);
			mshell->cmd_num = i;
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
