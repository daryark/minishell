/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/03 17:19:09 by btvildia         ###   ########.fr       */
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
	char		**tmp;
	char		*path;
	t_env_lst	*node;
	int			i;

	i = 0;
	node = NULL;
	path = NULL;
	tmp = mshell->cmdarr[mshell->cmd_num].args;
	if (!tmp[1])
	{
		node = find_env_node("HOME", mshell->env);
		if (node)
			path = ft_strdup(node->val);
		if (!path || chdir(path) == -1)
			return (ft_error_return("", mshell, 1, 1));
		ft_free(path);
	}
	else
	{
		if (chdir(tmp[1]) == -1)
			return (ft_error_return(tmp[1], mshell, 1, 0));
	}
	mshell->exit_status = 0;
}

void	ft_pwd(t_mshell *mshell)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_error_return(path, mshell, 1, 0));
	printf("%s\n", path);
	ft_free(path);
	mshell->exit_status = 0;
}

int	ft_exit(t_mshell *mshell, char *input)
{
	if (ft_strcmp("exit", mshell->cmdarr[0].args[0]) == 0)
	{
		ft_free(input);
		printf("exit\n");
		if (!mshell->cmdarr[0].args[1])
			exit(mshell->exit_status);
		else if (mshell->cmdarr[0].args[1]
			&& !ft_isdigit_loop(mshell->cmdarr[0].args[1]))
			ft_error_exit("exit: ", "numeric argument required", 2);
		else if (ft_isdigit_loop(mshell->cmdarr[0].args[1])
			&& mshell->cmdarr[0].args[2])
			return (ft_error_return("", mshell, 1, 0), 1);
		else if (mshell->cmdarr[0].args[1])
			exit(ft_atoi(mshell->cmdarr[0].args[1]));
	}
	return (0);
}
