/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 03:28:01 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/17 18:06:30 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_env(t_env_lst *env);

static int	fill_str(char *s, t_env_lst **lst)
{
	int		divider_pos;
	int		err;
	char	*val;
	char	*name;

	err = 0;
	divider_pos = ft_strchr_pos(s, '=');
	if (divider_pos >= 0)
	{
		name = ft_substr(s, 0, divider_pos - 1);
		val = ft_strdup(&(s[divider_pos]));
		if (!val || !name)
			err = 1;
		ft_lstadd_env(lst, name, val);
	}
	else
	{
		name = ft_strdup((char *)s);
		val = NULL;
		if (!name)
			err = 1;
		ft_lstadd_env(lst, name, val);
	}
	return (err);
}

void	init_env(t_mshell *mshell, char **env)
{
	int	i;

	i = 0;
	printf("env\n");
	while (env[i])
	{
		if (fill_str(env[i], &mshell->env))
		{
			clean_lst_env(&mshell->env);
			alloc_err();
		}
		i++;
	}
	// print_env(mshell->env);
}

void	print_env(t_env_lst *env)
{
	while (env)
	{
		printf("%s%s = %s%s%s\n", YELLOW, env->name, GREEN, \
			env->val, RE);
		env = env->next;
	}
}
