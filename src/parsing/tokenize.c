/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:34:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/26 00:14:17 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	pass_quoted_str(char *s, char *q)
{
	int	i;

	i = 0;
	i++;
	while (s[i] && s[i] != *q)
		i++;
	quote_opened_type(s[i], q);
	return (i);
}

int	pass_str(char *s)
{
	int		i;
	char	q;

	q = '\0';
	i = 0;
	while (s[i] && !spec_symb(&s[i]) && !space(s[i]))
	{
		quote_opened_type(s[i], &q);
		if (q)
		{
			i++;
			while (s[i] && s[i] != q)
				i++;
			quote_opened_type(s[i], &q);
		}
		i++;
	}
	return (i);
}

void	init_tokarr(char *s, t_mshell *mshell)
{
	int		len;
	int		i;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (space(s[i]))
			continue ;
		if (spec_symb(&s[i]))
		{
			if (spec_symb(&s[i]) == 2)
				i++;
		}
		else
			i += pass_str(&s[i]) - 1;
		len++;
	}
	mshell->tokarr = ft_malloc(sizeof(t_token) * (len + 1));
	if (!mshell->tokarr)
		alloc_err();
	set_default_arr(mshell->tokarr, len);
}

//arg - &s[i] ptr on needed str part
t_type	token_typizator(char *s)
{
	if (*s == '|')
		return (T_PIPE);
	else if (*s == *(s + 1) && *s == '<')
		return (T_HEREDOC);
	else if (*s == '<')
		return (T_RED_INP);
	else if (*s == *(s + 1) && *s == '>')
		return (T_APPEND);
	else if (*s == '>')
		return (T_RED_OUT);
	else
		return (T_WORD);
}
