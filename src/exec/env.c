/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:24 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/24 15:23:29 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_env(t_mshell *mshell)
{
	t_env_lst	*tmp;

	tmp = mshell->env;
	if (mshell->export)
	{
		while (tmp)
		{
			if (tmp->val)
				printf("%s=%s\n", tmp->name, tmp->val);
			tmp = tmp->next;
		}
		return ;
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "_", 1) != 0)
		{
			if (tmp->val)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->val);
			else
				printf("declare -x %s\n", tmp->name);
		}
		tmp = tmp->next;
	}
}

void	tmp_sort_env(t_env_lst *env)
{
	t_env_lst	*tmp;
	char		*tmp_name;
	char		*tmp_val;

	while (env)
	{
		tmp = env->next;
		while (tmp)
		{
			if (ft_strncmp(env->name, tmp->name, ft_strlen(env->name)) > 0)
			{
				tmp_name = env->name;
				tmp_val = env->val;
				env->name = tmp->name;
				env->val = tmp->val;
				tmp->name = tmp_name;
				tmp->val = tmp_val;
			}
			tmp = tmp->next;
		}
		env = env->next;
	}
}

static void	remove_one_node(char *str, t_env_lst **env)
{
	t_env_lst	*tmp;
	t_env_lst	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		//*don't understand why the check for 0 is right, but it doesn't go into (if)
		// printf("name:%s, %d\n", tmp->name, ft_strncmp(tmp->name, str, ft_strlen(str)));
		if (ft_strncmp(tmp->name, str, ft_strlen(str)) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			ft_free(tmp->name);
			ft_free(tmp->val);
			ft_free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_export(t_mshell *mshell)
{
	char		**tmp;
	int			i;
	char		*name;
	t_env_lst	*cpy_list;

	cpy_list = NULL;
	if (ft_strlen(mshell->input) == 6)
	{
		copy_list(mshell->env, &cpy_list);
		tmp_sort_env(cpy_list);
		mshell->export = cpy_list;
		remove_one_node("_", &mshell->export);
		ft_env(mshell);
		clean_lst_env(&cpy_list);
		cpy_list = NULL;
	}
	else
	{
		tmp = ft_split(mshell->input, ' ');
		i = 1;
		while (tmp[i])
		{
			name = cut_name(tmp[i]);
			if (!find_env_node(name, mshell->env))
				fill_str(tmp[i], &mshell->env);
			ft_free(name);
			i++;
		}
		ft_free(tmp);
	}
}

void	ft_unset(t_mshell *mshell)
{
	int		i;
	char	**rm_names;

	if (ft_strlen(mshell->input) == 5)
		return ;
	else
	{
		rm_names = ft_split(mshell->input, ' ');
		i = 1;
		while (rm_names[i] != NULL)
		{
			remove_one_node(rm_names[i], &mshell->env);
			i++;
		}
	}
}
