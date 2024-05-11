/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:22:23 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/11 19:12:51 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int space(char c)
{
    return (c == ' ' || c == '\t');
}

//set quote "|' or unset for '\0' if it was open with same quote type
void  quote_opened_type(char c, char *quote)
{
    if ((c == '\"' || c == '\'') && !*quote)
            *quote = c;
        else if ((c == '\"' || c == '\'') && *quote == c)
            *quote = '\0';
}

int arr_len(char **arr)
{
    int len;

    len = 0;
    while(*arr)
    {
        len++;
        arr++;
    }
    return (len);
}

int    ft_strchr_pos(char *s, int c)
{
    int i;

    i = 0;
    while (s[i] != (unsigned char)c && s[i])
            i++;
    if (s[i] == (unsigned char)c)
            return (++i);
    return (-1);
}