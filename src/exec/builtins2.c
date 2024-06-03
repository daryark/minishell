/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:31:17 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/03 11:56:20 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_env(t_mshell *mshell)
{
	t_env_lst	*tmp;

	tmp = mshell->env;
	if (!mshell->export)
	{
		while (tmp)
		{
			if (tmp->val)
				printf("%s=%s\n", tmp->name, tmp->val);
			tmp = tmp->next;
		}
		mshell->exit_status = 0;
		return ;
	}
	tmp = mshell->export;
	while (tmp)
	{
		if (tmp->val)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->val);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	mshell->exit_status = 0;
}

void	export_arg_loop(t_mshell *mshell, char **args, int i)
{
	char		*name;
	t_env_lst	*env_node;
	int			divider_pos;

	while (args[i])
	{
		name = cut_name(args[i]);
		if (args[i][ft_strlen(name)] && args[i][ft_strlen(name)] != '=')
		{
			ft_free(name);
			name = NULL;
		}
		if (!name)
			return (syntax_err(args[i], 4));
		env_node = find_env_node(name, mshell->env);
		if (!env_node)
			fill_str(args[i], &mshell->env);
		else
		{
			divider_pos = ft_strchr_pos(args[i], '=');
			if (divider_pos >= 0)
			{
				if (env_node->val)
					ft_free(env_node->val);
				env_node->val = ft_strdup(&args[i][divider_pos]);
			}
		}
		i++;
	}
}

void	ft_export(t_mshell *mshell)
{
	char	**args;

	args = mshell->cmdarr[mshell->cmd_num].args;
	if (args[1] == NULL)
	{
		copy_list(mshell->env, &mshell->export);
		remove_one_node("_", &mshell->export);
		tmp_sort_env(mshell->export);
		ft_env(mshell);
		clean_lst_env(&mshell->export);
	}
	else
		export_loop(mshell, args, 1);
	mshell->exit_status = 0;
}

void	ft_unset(t_mshell *mshell)
{
	int		i;
	char	**rm_names;

	rm_names = mshell->cmdarr[mshell->cmd_num].args;
	if (rm_names[1] == NULL)
	{
		printf("minishell: unset: not enough arguments\n");
		mshell->exit_status = 1;
		return ;
	}
	else
	{
		i = 1;
		while (rm_names[i] != NULL)
		{
			remove_one_node(rm_names[i], &mshell->env);
			i++;
		}
	}
	mshell->exit_status = 0;
}

int	ft_exit(t_mshell *mshell, char *input)
{
	if (ft_strcmp(mshell->cmdarr[0].args[0], "exit") == 0)
	{
		ft_free(input);
		printf("exit\n");
		if (!mshell->cmdarr[0].args[1])
			exit(mshell->exit_status);
		else if (mshell->cmdarr[0].args[1]
			&& !ft_isdigit(mshell->cmdarr[0].args[1][0]))
			ft_error_exit("exit: ", "numeric argument required", 2);
		else if (ft_isdigit(mshell->cmdarr[0].args[1][0])
			&& mshell->cmdarr[0].args[2])
		{
			ft_error_return("exit: ", "too many arguments", mshell, 1);
			return (1);
		}
		else if (mshell->cmdarr[0].args[1])
			exit(ft_atoi(mshell->cmdarr[0].args[1]));
	}
	return (0);
}
