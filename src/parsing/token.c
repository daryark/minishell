/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:29:53 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/15 18:34:43 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// void    add_quote_token(char c)
// {
//     if (*s == '\'')
//         add_token(c, 1, )
// }

void    prep_token(char *s, int len)
{
    if (len == 1)
    {
        if (*s == '|')
            add_token()
    }
}