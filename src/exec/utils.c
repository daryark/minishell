/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:46:01 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/01 22:57:17 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

int	ft_execve(char *cmds, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

	i = 0;
	cmd = ft_split(cmds, ' ');
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = find_path(cmd[0], envp[i]);
	i = 0;
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		exit(127);
	}
	execve(path, cmd, envp);
	free_array(cmd);
	free(path);
	return (0);
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
		free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			free_array(paths);
			return (c);
		}
		free(c);
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
