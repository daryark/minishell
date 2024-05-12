/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:43:20 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/12 17:56:18 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	dollars_replace(char **s, t_mshell *mshell)
{
	int	i;

	// int quote;
	// int search_name;
	i = -1;
	while ((*s)[++i])
	{
		if ((*s)[i] == '$')
		{
			if ((*s)[i + 1] == '?')
				dollar_question_replace(s, i, mshell);
			// else
		}
	}
	// find $:
	//--when single quote is not open
	// if ? next -> replace with exit code of prev command
	// if not found -> just return "" instead of ?
	// else read until space(char c) and find in env[i].name
	// if not found -> just return "" instead of name
	//--in both cases split dst, add place for replacement str
	//  fill the replacing str, join all.
}

static void	trim_input(char *src, char *dst)
{
	int		i;
	int		d;
	char	quote;

	i = -1;
	d = 0;
	quote = '\0';
	if (!src || !dst)
		return ;
	while (src[++i])
	{
		quote_opened_type(src[i], &quote);
		if (!(((space(src[i]) && space(src[i + 1])) || (space(src[i]) && (!d
							|| !src[i + 1]))) && !quote))
			dst[d++] = src[i];
	}
}

void	parse_input(char *input, t_mshell *mshell)
{
	char	*dst;

	if (input_err_check(input))
		return ;
	dst = (char *)ft_calloc(sizeof(char), ft_strlen(input) + 1);
	if (!dst)
		exit(printf(RED "Allocation failed\n" RE));
	// printf("input: |%s|\n", input);
	trim_input(input, dst);
	// printf(" trim: |%s|\n", dst);
	// split
	dollars_replace(&dst, mshell);
	mshell->input = dst;
}
