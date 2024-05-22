/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 03:28:01 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/20 14:34:22 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_env(t_env_lst *env);

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

//*Please, don't use this fn!!!!
//*just add fn to change/add/remove needed name/value in the lst
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
	// print_env(mshell->env);
}

// it can be used when env command is inputed
void	print_env(t_env_lst *env)
{
	while (env)
	{
		printf("%s%s = %s%s%s\n", YELLOW, env->name, GREEN, env->val, RE);
		env = env->next;
	}
}
