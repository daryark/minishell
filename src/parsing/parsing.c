/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:43:20 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/17 01:32:05 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// static void	replace_dollars(char **s, t_mshell *mshell)
// {
// 	char	**dllr_arr;
// 	int		i;
// 	char	q;

// 	dllr_arr = split_parts(*s, '$');
// 	if (!dllr_arr)
// 		alloc_err();
// 	q = '\0';
// 	i = -1;
// 	while (dllr_arr[++i])
// 		dollar_value_subst(&dllr_arr[i], &q, mshell);
	//!------------------------------------------------------
	// int		i;
	// char	*re_str;

	// int quote;
	// int search_name;
	// i = -1;
	// while ((*s)[++i])
	// {
	// 	if ((*s)[i] == '$')
	// 	{
	// 		if ((*s)[i + 1] == '?')
	// 		{	
	// 			re_str = ft_itoa(mshell->exit_status);
	// 			if (!re_str)
	// 				exit(printf(RED "Allocation failed\n" RE));
	// 			dollar_question_replace(s, i, re_str, mshell);
	// 		}
	// 		else
	// 		{
	// 			// re_str =  
	// 		}
	// 	}
	// }
	// find $:
	//--when single quote is not open
	// if ? next -> replace with exit code of prev command
	// if not found -> just return "" instead of ?
	// else read until space(char c) and find in env[i].name
	// if not found -> just return "" instead of name
	//--in both cases split dst, add place for replacement str
	//  fill the replacing str, join all.
// }

static void	split_tokens(char *s, t_mshell *mshell)
{
	// char q;

	// q = '\0';
	init_token_arr(s, mshell);
	// while (*s)
	// {
	// 	quote_opened_type(*s, &q);
	// 	if (quote(*s) && q)
	// 		add_quote_token(*s);
	// 	else if (*s == '|')
	// 		add_token(*s, 1, T_PIPE);
	// 	else if (*s == '<' || *s == '>')
	// 		printf("REDIR\n");
	// 	else
	// 		printf("c");
	// 	s++;
	// }
}

static void	trim_input(char *src, char *dst)
{
	int		i;
	int		d;
	char	q;

	i = -1;
	d = 0;
	q = '\0';
	if (!src || !dst)
		return ;
	while (src[++i])
	{
		quote_opened_type(src[i], &q);
		if (!(((space(src[i]) && space(src[i + 1]))
			|| (space(src[i]) && (!d || !src[i + 1]))) && !q))
			dst[d++] = src[i];
	}
}

int	parse_input(char *input, t_mshell *mshell)
{
	char	*dst;

	if (input_err_check(input))
		return (1);
	dst = (char *)ft_calloc(sizeof(char), ft_strlen(input) + 1);
	if (!dst)
		alloc_err();
	trim_input(input, dst);
	printf("%s trim: |%s|\n%s", GREEN, dst, RE);

	// replace_dollars(&dst, mshell);
	split_tokens(dst, mshell);
	mshell->input = dst;
	return (0);
}

