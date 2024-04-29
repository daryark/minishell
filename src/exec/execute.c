/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/30 00:44:27 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	execute_command(char *cmd, char **envp)
{
	char	**cmds;
	int		i;
	int		fd[2];
	int		fd_in;

	cmds = ft_split(cmd, '|');
	i = 0;
	fd_in = 0;
	while (cmds[i] != NULL)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(fd_in, 0);
			if (cmds[i + 1] != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			if (ft_execve(cmds[i], envp) == 1)
				break ;
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fd_in = fd[0];
			i++;
		}
	}
	free_array(cmds);
}

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
		return (1);
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
