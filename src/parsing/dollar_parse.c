/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:30:07 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/12 02:19:42 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void    dollar_question_replace(char **s, int i, t_mshell *mshell)
{
    char    *start;
    char    *end;
    char    *mid;
    int     end_len;
    char    *half_str;

    half_str = NULL;
    mid = NULL;
    start = (char *)ft_calloc(sizeof(char), i + 1);
    end_len = ft_strlen(&(*s)[i + 1]);
    end = (char *)ft_calloc(sizeof(char), ft_strlen(&(*s)[i + 1]));
    if (!start || !end)
        exit(printf(RED "Allocation failed\n" RE));
    start = ft_substr(*s, 0, i + 1);
    end = ft_substr(*s, i + 2, end_len);
    free(*s);
    mid = ft_itoa(mshell->exit_status);
    half_str = ft_strjoin(start, mid);
    free(half_str);
    *s = ft_strjoin(half_str, end);
}