/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:22:23 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/17 23:24:51 by dyarkovs         ###   ########.fr       */
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

int	arr_len(char **arr)
{
	int	len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

//finds position from start of s. 
//Not iteration(from 0), iterates from 1!
int	ft_strchr_pos(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (unsigned char)c && s[i])
		i++;
	if (s[i] == (unsigned char)c)
		return (++i);
	return (-1);
}
