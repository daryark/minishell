/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:23:05 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/28 15:33:01 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	space(char c)
{
	return (c == ' ' || c == '\t');
}

int	quote(char c)
{
	if (c == '\"')
		return ('\"');
	if (c == '\'')
		return ('\'');
	else
		return (0);
}

// set quote "|' or unset for '\0' if it was open with same quote type
void	quote_opened_type(char c, char *q)
{
	if ((quote(c)) && !*q)
		*q = c;
	else if ((quote(c)) && *q == c)
		*q = '\0';
}

//takes ptr on i being comapred, if needed - takes i+1
int	spec_symb(char *s)
{
	if (*s == '|')
		return (1);
	else if (*s == '<')
	{
		if ((*(s + 1) && *(s + 1) == '<') ||
			(*(s + 1) && *(s + 1) == '>'))
			return (2);
		return (1);
	}
	else if (*s == '>')
	{
		if (*(s + 1) && *(s + 1) == '>')
			return (2);
		return (1);
	}
	return (0);
}
