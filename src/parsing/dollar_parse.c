/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:30:07 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/17 01:31:27 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//s - whole str, i - position of $ to divide str
//re_str  =
// void	dollar_replace(char **s, int st, int en, t_mshell *mshell)
// {
// 	char	*start;
// 	char	*end;
// 	char	*mid;
// 	char	*half_str;

// 	start = ft_substr(*s, 0, st + 1);
// 	end = ft_substr(*s, st + 2, ft_strlen(&(*s)[st + 1]));
// 	mid = ft_itoa(mshell->exit_status);
// 	if (!start || !end || !mid)
// 		alloc_err();
// 	half_str = ft_strjoin(start, mid);
// 	ft_free(start);
// 	ft_free(mid);
// 	ft_free(*s);
// 	*s = ft_strjoin(half_str, end);
// 	ft_free(half_str);
// 	ft_free(end);
// }

// char *find_env_var(char *name, char **env)
// {
// 	char *value;

// 	value = NULL;
// 	(void)name;
// 	(void)env;
// 	return (value);
// }

void	dollar_value_subst(char **s, char *q, t_mshell *mshell)
{
	char	*new;
	int		i;
	char	*name;

	(void)new;
	(void)name;
	(void)i;
	(void)s;
	(void)q;
	(void)mshell;
	// //spec cases
	// if (((*s)[0] == '$' && (((*s)[1] == space((*s)[1]) || !(*s)[1])
	// 			|| q && ((*s)[1] == spec_symb(*s, 1) || quote((*s)[1]))
	// 			|| (q == '\''))) || (*s)[0] != '$')
	// 	new = ft_strdup(*s);
	// else if (!q && (*s)[1] == spec_symb(*s, 1) || quote((*s)[1]))
	// 	new = "";
	// else if ((*s)[1] == '?' && (*s)[2]) //question sign
	// 	new = ft_strjoin(ft_itoa(mshell->exit_status), &(*s)[2]);
	// else if ((*s)[1] == '?' && !(*s)[2])
	// 	new = ft_itoa(mshell->exit_status);
	// else //other type of input (alphanumeric characters) in "" or without any
	// {
	// 	i = 1;
	// 	while ((*s)[i] && ft_isalnum((*s)[i]))
	// 		i++;
	// 	name = ft_substr(*s, 1, --i);
	// 	//find name in env (if there is name and no next char in both env.name && no next char in name), then take its value;
	// 	find_env_var(name, mshell->env);
	// }
	// i = -1;
	// while ((*s)[++i])
	// 	quote_opened_type((*s)[i], q);
	// free(*s);
	// *s = new;
}
