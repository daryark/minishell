/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:04:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/11 03:00:18 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void    trim_input(char *src, char *dst)
{
    int d;

    d = -1;
    while (*src)
    {
        //while found ' and didn't found second the same
        //OR
        //while found " and didn't found second the same
        //what should this fn reutrn, or what add inside curr fn?
        while (*src && in_quotes(&*src))
            dst[++d] = *src;
        while (!((*src == ' ' || *src == '\t') &&
            (*(src + 1) == ' ' || *(src + 1) == '\t')) &&
            !((*src == ' ' || *src == '\t') && d != -1))
            dst[++d] = *src;
        src++;
    }
    if (dst[d] == ' ' || dst[d] == '\t')
        dst[d] = '\0';

    
}

void parse_input(char *input, t_mshell *mshell)
{
    char *dst;

    (void)mshell;
    dst = ft_calloc(sizeof(char), ft_strlen(input) + 1);
    trim_input(input, dst);
    if (parse_err(input))
        return ;
    printf("parsing input   ");
}