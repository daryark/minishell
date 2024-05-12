/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/12 16:05:28 by btvildia         ###   ########.fr       */
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

char	*ft_remove_substr(char *str, char *sub)
{
	char	*result;
	char	*found;
	int		len;
	int		new_len;
	int		i;

	result = NULL;
	if (!str || !sub)
		return (NULL);
	found = ft_strnstr(str, sub, ft_strlen(str));
	if (found)
	{
		len = ft_strlen(sub);
		new_len = ft_strlen(str) - len;
		result = (char *)malloc((new_len + 1) * sizeof(char));
		if (result)
		{
			i = found - str;
			ft_strncpy(result, str, i);
			ft_strncpy(result + i, found + len, new_len - i);
			result[new_len] = '\0';
		}
	}
	return (result);
}
