/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:54:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/02 00:36:13 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	wait_in_parent(t_mshell *mshell)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < mshell->cmdarr_l)
	{
		wait(&status);
		if (WIFEXITED(status))
			mshell->exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	open_fds(t_mshell *mshell, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < mshell->cmdarr_l - 1)
	{
		pipe(pipes[i]);
		i++;
	}
}

void	close_fds(t_mshell *mshell, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < mshell->cmdarr_l - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	return_builtin_num(char *cmd)
{
	if (!cmd)
		return (-1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (2);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (3);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (5);
	return (-1);
}

void	ft_execve(t_mshell *mshell)
{
	char	*path;
	char	**cmds;
	char	**envp;

	path = NULL;
	envp = convert_env(mshell->env);
	cmds = mshell->cmdarr[mshell->cmd_num].args;
	while (mshell->env)
	{
		if (ft_strncmp(mshell->env->name, "PATH", 4) == 0)
			break ;
		mshell->env = mshell->env->next;
	}
	if (ft_strchr(cmds[0], '/') == NULL)
		path = find_path(cmds[0], mshell->env->val);
	else
		path = ft_strdup(cmds[0]);
	if (path == NULL)
		ft_error_exit(cmds[0], ": command not found\n", 127);
	execve(path, cmds, envp);
	if (cmds[0] != NULL)
		ft_error_exit(cmds[0], ": command not found\n", 127);
	exit(0);
}
