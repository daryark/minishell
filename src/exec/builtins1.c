/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/03 14:02:13 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	init_builtin_arr(t_mshell *mshell)
{
	int	n_cmds;

	n_cmds = 6;
	mshell->builtin = ft_malloc(sizeof(t_builtin) * (n_cmds + 1));
	mshell->builtin[0].name = "pwd";
	mshell->builtin[0].fn_ptr = ft_pwd;
	mshell->builtin[1].name = "cd";
	mshell->builtin[1].fn_ptr = ft_cd;
	mshell->builtin[2].name = "echo";
	mshell->builtin[2].fn_ptr = ft_echo;
	mshell->builtin[3].name = "unset";
	mshell->builtin[3].fn_ptr = ft_unset;
	mshell->builtin[4].name = "export";
	mshell->builtin[4].fn_ptr = ft_export;
	mshell->builtin[5].name = "env";
	mshell->builtin[5].fn_ptr = ft_env;
	mshell->builtin[6].name = NULL;
	mshell->builtin[6].fn_ptr = NULL;
}

void	ft_cd(t_mshell *mshell)
{
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	tmp = mshell->cmdarr[mshell->cmd_num].args;
	if (!tmp[1])
	{
		path = ft_strdup(find_env(mshell->env, "HOME"));
		if (!path || chdir(path) == -1)
		{
			ft_error_return("cd: ", "HOME not set", mshell, 1);
			return ;
		}
		ft_free(path);
	}
	else
	{
		if (chdir(tmp[1]) == -1)
		{
			ft_error_return("cd: ", "No such file or directory", mshell, 1);
			return ;
		}
	}
	mshell->exit_status = 0;
}

void	ft_pwd(t_mshell *mshell)
{
	char	*path;

	if (mshell->cmdarr[mshell->cmd_num].args)
	{
		ft_error_return("pwd: ", "too many arguments", mshell, 1);
		return ;
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_error_return("pwd: ", "error retrieving current directory", mshell,
			1);
		return ;
	}
	printf("%s\n", path);
	ft_free(path);
	mshell->exit_status = 0;
}
