/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:09:10 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/31 16:16:07 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

char	**get_envp(char **envp)
{
	char	**basic_env;

	if (envp && *envp)
		return (envp);
	else
	{
		basic_env = ft_malloc(sizeof(char *) * 9);
		basic_env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
		basic_env[1] = ft_strdup("PWD=/");
		basic_env[2] = ft_strdup("SHLVL=1");
		basic_env[3] = ft_strdup("HOME=/");
		basic_env[4] = ft_strdup("LOGNAME=user");
		basic_env[5] = ft_strdup("USER=user");
		basic_env[6] = ft_strdup("LANG=C");
		basic_env[7] = ft_strdup("TERM=xterm-256color");
		basic_env[8] = NULL;
		return (basic_env);
	}
}

// ☹ ☻
char	*exit_status_smile(char *tmp2, t_mshell *mshell)
{
	char	*tmp;

	if (mshell->exit_status == 0)
		printf(BLUE "(%d)" RE, mshell->exit_status);
	else
		printf(RED "(%d)" RE, mshell->exit_status);
	tmp = ft_strjoin(YELLOW "Minishell~" RE, tmp2);
	return (tmp);
}

char	*get_currect_path(t_mshell *mshell)
{
	static char	*path;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	while (mshell->env)
	{
		if (!ft_strncmp(mshell->env->name, "USER", 5))
			break ;
		mshell->env = mshell->env->next;
	}
	tmp3 = getcwd(NULL, 0);
	if (!tmp3)
	{
		printf("\nyou can use only 'cd ..' or 'exit'\n\n");
		return (path);
	}
	tmp = ft_strjoin("/home/", mshell->env->val);
	tmp2 = ft_strjoin(ft_remove_substr(tmp3, tmp), "$ ");
	ft_free(tmp3);
	path = exit_status_smile(tmp2, mshell);
	ft_free(tmp2);
	ft_free(tmp);
	return (path);
}
