/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/20 14:19:11 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_execute(t_mshell *mshell)
{
	if (ft_strncmp(mshell->input, "cd", 2) == 0)
		ft_cd(mshell);
	else if (ft_strncmp(mshell->input, "echo", 4) == 0)
		ft_echo(mshell);
	else if (ft_strncmp(mshell->input, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(mshell->input, "env", 3) == 0)
		ft_env(mshell->env, 0);
	else if (ft_strncmp(mshell->input, "export", 6) == 0)
		ft_export(mshell);
	else if (ft_strncmp(mshell->input, "unset", 5) == 0)
		ft_unset(mshell);
	else
		ft_exec_just_cmd(mshell);
}

void	ft_cd(t_mshell *mshell)
{
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	while (mshell->envp[i] && ft_strncmp(mshell->envp[i], "USER=", 5) != 0)
		i++;
	tmp = ft_split(mshell->input, ' ');
	if (tmp[1] == NULL)
	{
		path = ft_strjoin("/home/", mshell->envp[i] + 5);
		chdir(path);
		ft_free(path);
	}
	else
	{
		chdir(tmp[1]);
		ft_free(tmp[1]);
	}
	ft_free(tmp);
}

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	ft_free(path);
}
