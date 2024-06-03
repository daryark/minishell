/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 03:28:01 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/03 15:14:06 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	set_shlvl(t_mshell *mshell)
{
	t_env_lst	*shlvl_node;
	int			shlvl;

	shlvl_node = find_env_node("SHLVL", mshell->env);
	shlvl = ft_atoi(shlvl_node->val);
	ft_free(shlvl_node->val);
	if (shlvl == 999)
	{
		printf("mminishell: warning: shell level (1000) too high, resetting to 1\n");
		shlvl_node->val = "1";
	}
	else
		shlvl_node->val = ft_itoa(shlvl + 1);
}

int	fill_str(char *s, t_env_lst **lst)
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
	while (env[i])
	{
		if (fill_str(env[i], &mshell->env))
		{
			clean_lst_env(&mshell->env);
			alloc_err();
		}
		i++;
	}
	set_shlvl(mshell);
}
