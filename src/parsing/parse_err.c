/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:00:05 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/10 23:44:38 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int open_quotes(char *s)
{
    int i;
    int single_q;
    int double_q;

    single_q = 0;
    double_q = 0;
    i = -1;
    while (s[++i])
    {
        if (s[i] == '\'' && !double_q)
            single_q = (single_q + 1) % 2;
        if (s[i] == '\"' && !single_q)
            double_q = (double_q + 1) % 2;
        // printf("%d,%d  \n", single_q, double_q);
    }
    return (single_q || double_q);
}

static int redir_err(char *s)
{
    (void)s;
    return (0);
}

static int not_valid_symbols(char *s)
{
    (void)s;
    return (0);
}

int parse_err(char *input)
{
    if (open_quotes(input))
        return (printf("syntax error: unable to locate closing quotation\n")); 
    if (redir_err(input) || not_valid_symbols(input))
    {
        return (printf("parsing error\n"));
    }
    return (0);
}