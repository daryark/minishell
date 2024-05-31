/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:24 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/31 12:44:46 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

char	*find_env(t_env_lst *env, char *name)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**convert_env(t_env_lst *env)
{
	t_env_lst	*tmp;
	char		**envp;
	int			i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->name, "=");
		if (tmp->val)
			envp[i] = ft_strjoin(envp[i], tmp->val);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

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
	int			i;
	char		*name;
	char		**args;
	t_env_lst	*env_node;
	int			divider_pos;

	args = mshell->cmdarr[mshell->cmd_num].args;
	env_node = NULL;
	if (args[1] == NULL)
	{
		copy_list(mshell->env, &mshell->export);
		remove_one_node("_", &mshell->export);
		tmp_sort_env(mshell->export);
		ft_env(mshell);
		clean_lst_env(&mshell->export);
	}
	else
	{
		i = 1;
		while (args[i])
		{
			name = cut_name(args[i]);
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
}
