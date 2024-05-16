/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:30:07 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/16 18:04:39 by dyarkovs         ###   ########.fr       */
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

void	dollar_value_subst(char **s, char *q, t_mshell *mshell)
{
	(void)s;
	(void)q;
	(void)mshell;
	// printf("\nin dollar val subst fn\n");
	// if ((*s)[1] == '?')
	// {
	// 	if (!(*s[2]))
			//str to replace = ft_atoi(); //mshell add to args!!!
	// }
}