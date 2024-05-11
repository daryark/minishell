/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 03:28:01 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/10 22:08:47 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incl/minishell.h"


static void arr_clean(t_env_line *env)
{
	while (env)
	{
		free(env->name);
		if (env->val != NULL)
		free(env->val);
		env++;
	}
	free(env);
	env = NULL;
}

static int fill_str(char *s, t_env_line *s_line)
{
	int divider_pos;
	int err;

	err = 0;
	divider_pos = ft_strchr_pos(s, '=');
	if (divider_pos >= 0)
	{
		s_line->name = ft_substr(s, 0, divider_pos - 1);
		s_line->val = ft_strdup(&(s[divider_pos]));
		if (!s_line->val || !s_line->name)
			err = 1;
	}
	else
	{
		s_line->name = ft_strdup((const char *)s);
		s_line->val = NULL;
		if (!s_line->name)
			err = 1;
	}
	return (err);
}

void init_env(t_mshell *mshell, char **env)
{
	int i;
	
	mshell->env = (t_env_line *)ft_calloc(sizeof(t_env_line *), arr_len(env));
	if (!mshell->env)
		exit(printf(RED "Allocation failed\n" RE));
	i = -1;
	while(env[++i])
	{
		if (fill_str(env[i], &mshell->env[i]))
		{
			arr_clean(mshell->env);
			exit(printf(RED "Allocation failed\n" RE));
		}
		// printf("%s%s = %s%s%s\n", YELLOW, mshell->env[i].name, GREEN, mshell->env[i].val, RE);
	}

}
