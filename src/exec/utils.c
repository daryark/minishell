/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/12 14:51:06 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_cd(char *cmd)
{
	char	**tmp;
	char	*path;

	tmp = ft_split(cmd, ' ');
	if (tmp[1] == NULL)
	{
		path = ft_strdup("/home");
		chdir(path);
		free(path);
	}
	else
	{
		chdir(tmp[1]);
		free(tmp[1]);
	}
	free(tmp);
}

void	ft_echo(char *cmd)
{
	char	**tmp;
	int		i;

	tmp = ft_split(cmd, ' ');
	i = 1;
	while (tmp[i] != NULL)
	{
		printf("%s", tmp[i]);
		if (tmp[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
	free(tmp);
}

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}

void	ft_env(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->envp[i] != NULL)
	{
		printf("%s\n", mshell->envp[i]);
		i++;
	}
}

void	ft_exec_just_cmd(char *cmd, t_mshell *mshell)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		ft_execve(cmd, mshell->envp);
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
