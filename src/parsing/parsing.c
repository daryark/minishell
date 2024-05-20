/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:43:20 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/20 22:58:36 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
		if (!(((space(src[i]) && space(src[i + 1])) || (space(src[i]) && (!d
							|| !src[i + 1]))) && !q))
			dst[d++] = src[i];
	}
}

static void	replace_dollars(char **s, t_mshell *mshell)
{
	char	**dllr_arr;
	int		i;
	char	q;

	dllr_arr = split_save_divider(*s, '$');
	if (!dllr_arr)
		alloc_err();
	q = '\0';
	i = -1;
	while (dllr_arr[++i])
		dollar_value_subst(&dllr_arr[i], &q, mshell);
	ft_free(*s);
	i = -1;
	while (dllr_arr[++i])
	{
		if (!i)
			*s = ft_strdup(dllr_arr[i]);
		if (dllr_arr[i + 1])
			*s = ft_strjoin(*s, dllr_arr[i + 1]);
		if (!*s)
			alloc_err();
	}
	ft_free_array(dllr_arr);
}

static void	split_tokens(char *s, t_mshell *mshell)
{
	// char	q;
	// int		i;

	// q = '\0';
	// i = -1;
	
		//space && !q . Cut space, pass through
		// spec_symb && !q . Just separate spec_symb into token

	// printf("--------------------------%stokens%s\n", GREEN, RE);
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
	// printf("--------------------------%stokens END%s\n\n\n", GREEN, RE);
}



int	parse_input(char *input, t_mshell *mshell)
{
	char	*dst;

	(void)mshell;
	if (input_err_check(input))
		return (1);
	dst = (char *)ft_calloc(sizeof(char), ft_strlen(input) + 1);
	if (!dst)
		alloc_err();
	trim_input(input, dst);
	printf("%s trim: |%s|\n%s", GREEN, dst, RE);
	replace_dollars(&dst, mshell);
	printf("%s $: |%s|\n%s", GREEN, dst, RE);
	split_tokens(dst, mshell);
	mshell->input = dst;
	return (0);
}
