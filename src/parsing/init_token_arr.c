/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:34:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/15 19:55:06 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/parsing.h"

int spec_symb(char c)
{
    return (c == '<' || c == '>' || c == '|'
        || c == '\'' || c == '\"' || space(c));
}

int pass_str(char *s, char q)
{
    int i;

    i = 0;
    if (q)
    {
        while (s[i] && s[i] != q)
            i++;
    }
    else
    {
        while (s[i] && !spec_symb(s[i]))
            i++;
    }
    return (i);
}

void init_token_arr(char *s, t_mshell *mshell)
{
    int len;
    char q;
    int  i;

    len = 0;
    q = '\0';
    i = -1;
    while (s[++i])
    {
        quote_opened_type(s[i], &q);
        if ((spec_symb(s[i]) && !q) || s[i] == q)
            len++;
        else
        {    
            i += pass_str(&s[i], q);
            len++;
        }
    }
    mshell->s_token_arr = malloc(sizesof(t_token_arr) * len);
}