/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:54:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/31 12:06:47 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0644);
	else if (i == 3)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		printf("minishell: %s: %s\n", argv, strerror(errno));
		exit(2);
	}
	return (file);
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
	{
		write(2, "minishell: command not found\n", 29);
		ft_free_array(cmds);
		mshell->exit_status = 127;
		exit(127);
	}
	execve(path, cmds, envp);
	perror("execve");
	ft_free_array(cmds);
	mshell->exit_status = 127;
	exit(127);
}
