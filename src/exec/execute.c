/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/16 18:55:30 by btvildia         ###   ########.fr       */
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

char	*find_path(char *cmd, char *path)
{
	char	*c;
	char	*tmp;
	char	**paths;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(path + 5, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		c = ft_strjoin(tmp, cmd);
		ft_free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			ft_free_array(paths);
			return (c);
		}
		free(c);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

void	ft_execve(char *cmd, char **envp)
{
	char	**tmp_split;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	tmp_split = ft_split(cmd, ' ');
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (ft_strchr(tmp_split[0], '/') == NULL)
		path = find_path(tmp_split[0], envp[i]);
	else
		path = ft_strdup(tmp_split[0]);
	if (path == NULL)
	{
		printf("minishell: %s: command not found\n", tmp_split[0]);
		ft_free_array(tmp_split);
		exit(127);
	}
	execve(path, tmp_split, envp);
	printf("minishell: %s: command not found\n", tmp_split[0]);
	ft_free_array(tmp_split);
	exit(127);
}
