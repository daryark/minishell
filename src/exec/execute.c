/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/13 18:56:26 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_exec_just_cmd(t_mshell *mshell)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		ft_execve(mshell->input, mshell->envp);
	else
		waitpid(pid, &status, 0);
}

void	ft_execve(char *cmd, char **envp)
{
	char	**tmp_split;
	char	*path;
	int		i;

	tmp_split = ft_split(cmd, ' ');
	path = ft_strdup("/bin/");
	path = ft_strjoin(path, tmp_split[0]);
	i = execve(path, tmp_split, envp);
	if (i == -1)
	{
		printf("minishell: %s: command not found\n", tmp_split[0]);
		exit(127);
	}
}
