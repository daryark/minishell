/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:24 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/20 16:47:29 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_env(t_env_lst *env, int i)
{
	t_env_lst	*tmp;

	tmp = env;
	if (i == 0)
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

void	ft_export(t_mshell *mshell)
{
	char		**tmp;
	int			i;
	t_env_lst	*cpy_list;

	cpy_list = NULL;
	if (ft_strlen(mshell->input) == 6)
	{
		copy_list(mshell->env, &cpy_list);
		tmp_sort_env(cpy_list);
		ft_env(cpy_list, 1);
		clean_lst_env(&cpy_list);
	}
	else
	{
		tmp = ft_split(mshell->input, ' ');
		i = 1;
		while (tmp[i])
		{
			fill_str(tmp[i], &mshell->env);
			i++;
		}
		ft_free(tmp);
	}
}

void	remove_one_node(char *str, t_env_lst **env)
{
	t_env_lst	*tmp;
	t_env_lst	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
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
