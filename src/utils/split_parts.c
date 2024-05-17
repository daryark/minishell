/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:27:34 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/17 20:53:31 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//if no $, then add +1 char to print
//(as with $ found I do -1 $ from end of str in outside fn)
static int check_end_len(char *s, int len)
{
	if (len < 0)
		len = ft_strlen(s) + 1;
	if (!len)
		len = 2;
	return (len);
}

//! DIVIDE THE FUNC INTO PARTS
char	**split_parts(char *s, char c)
{
	int     i;
	int		a_i;
	int		w_l;
	int     len;
	char    **arr;

	i = -1;
	len = 1;
	while (s[++i])
	{
		if (!i && s[0] == c)
			i++;
		if (s[i] == c)
			len++;
	}
	arr = (char **)ft_calloc(sizeof(char *), len + 1);
	a_i = 0;
	i = 0;
	printf("arr len:%d\n", len);
	while (len--)
	{
		if (!i && s[i] != c)
		{
			w_l = ft_strchr_pos(&s[i], '$');
			check_end_len(&s[i], w_l);
			arr[a_i] = ft_substr(s, i, --w_l);
		}
		else
		{
			w_l = ft_strchr_pos(&s[i + 1], '$');
			check_end_len(&s[i], w_l);
			arr[a_i] = ft_substr(s, i, w_l);
		}
		printf("w_l: %d	", w_l);
		if (!arr[a_i])
			alloc_err();
		printf(" %s\n", arr[a_i]);
		i += w_l;
		a_i++;
	}
	return (arr);
}

