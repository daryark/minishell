/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:22:23 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/19 14:54:40 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// finds position from start of s.
// Not iteration(from 0), iterates from 1!
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

// int	empty_str(char *s)
// {
// 	if (!s)
// 		return (1);
// 	while (*s && space(*s))
// 		s++;
// 	if (*s)
// 		return (0);
// 	return (1);
// }