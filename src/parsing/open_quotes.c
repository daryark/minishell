/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:35:43 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/30 13:19:36 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*alloc_new_tok_len(t_token tok)
{
	char	q;
	int		len;
	char	*new;

	q = '\0';
	len = 0;
	// printf("alloc_new_tok_len\n");
	while (*tok.word && tok.type == T_WORD)
	{
		if (!(q == *tok.word || (!q && *tok.word == quote(*tok.word))))
		{
			len++;
		}
		quote_opened_type(*tok.word, &q);
		tok.word++;
	}
	// printf("len:%d\n", len);
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		alloc_err();
	return (new);
}

static void	open_token_quotes(t_token *tok)
{
	char	q;
	int		i;
	int		n_i;
	char	*new;

	q = '\0';
	i = -1;
	n_i = 0;
	// printf("open token quotes: %s\n", tok->word);
	if (tok->type > T_WORD)
		return ;
	new = alloc_new_tok_len(*tok);
	// printf("after alloc new\n");
	while (tok->word[++i])
	{
		// printf("i: %d, n_i:%d\n", i, n_i);
		if (!(q == tok->word[i] || (!q && tok->word[i] == quote(tok->word[i]))))
		{
			new[n_i] = tok->word[i];
			n_i++;
		}
		quote_opened_type(tok->word[i], &q);
	}
	ft_free(tok->word);
	tok->word = new;
}

void	open_quotes(t_mshell *mshell)
{
	int		a_i;

	a_i = -1;
	while (++a_i < mshell->tokarr_l)
		open_token_quotes(&mshell->tokarr[a_i]);
	// printf("%squotes opened%s\n", GREEN, RE);
}
