/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:43:20 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/22 19:31:54 by dyarkovs         ###   ########.fr       */
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
	q = '\0';
	i = -1;
	while (dllr_arr[++i])
		dollar_value_subst(&dllr_arr[i], &q, mshell);
	ft_free(*s);
	*s = arrjoin(dllr_arr);
	ft_free_array(dllr_arr);
}

static void	split_tokens(char *s, t_mshell *mshell)
{
	int		i;
	int		a_i;
	int		w_l;

	i = -1;
	a_i = 0;
	init_token_arr(s, mshell);
	while (s[++i])
	{
		if (space(s[i]))
			continue ;
		mshell->tokarr[a_i].type = token_typizator(&s[i]);
		w_l = spec_symb(&s[i]);
		if (!w_l)
			w_l = pass_str(&s[i]);
		mshell->tokarr[a_i].word = ft_substr(s, i, w_l--);
		i += w_l;
		printf("%s%s%s	", GREEN, mshell->tokarr[a_i].word, RE);
		printf("%s%d%s\n", YELLOW, mshell->tokarr[a_i].type, RE);
		a_i++;
	}
}

// static void	open_quotes(t_token *arr)
// {
// 	int	a_i;
// 	int	i;

// 	a_i = -1;
// 	while (arr[++a_i].word)
// 	{
// 		i = -1;
// 		while (arr[a_i].word[++i])
// 		{
			
// 		}
		
// 	}
// }


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
	// open_quotes(mshell);
	//check errors (if near < is not a word from both sides, if smth is from both sides of | ...)
	mshell->input = dst;
	ft_free(dst);
	return (0);
}
