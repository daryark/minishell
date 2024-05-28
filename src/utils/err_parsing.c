/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:00:05 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/28 19:51:38 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	open_quotes(char *s)
{
	int	i;
	int	single_q;
	int	double_q;
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

int	token_order_check(t_mshell *mshell)
{
	int		i;
	t_token	*arr;

	i = -1;
	arr = mshell->tokarr;
	while (++i < mshell->tokarr_l)
	{
		if (arr[i].type == T_PIPE && ((i - 1) < 0
				|| (i + 1) >= mshell->tokarr_l))
			return (syntax_err(arr[i].word), 1);
		else if (arr[i].type > 1 && (i + 1) >= mshell->tokarr_l)
			return (syntax_err("newline"), 1);
		else if (arr[i].type > 1 && mshell->tokarr[i + 1].type > 1)
			return (syntax_err(arr[i + 1].word), 1);
	}
	return (0);
}
static int	not_valid_symbols(char *s)
{
	char	quote;

	quote = '\0';
	while (*s)
	{
		quote_opened_type(*s, &quote);
		if ((*s == '&' || *s == ';' || *s == '\\') && !quote)
			return (*s);
		s++;
	}
	return (0);
}

void	syntax_err(char *c)
{
	if (*c == '\'' && !(*c + 1))
		printf("Minishell: syntax error: unable to locate closing quotation\n");
	else
		printf("Minishell: syntax error near unexpected token `%s'\n", c);
}

int	input_err_check(char *input)
{
	int	err_c;

	err_c = 0;
	if (open_quotes(input))
		return (syntax_err("\'"), 1);
	err_c = not_valid_symbols(input);
	if (err_c)
		return (syntax_err((char *)&err_c), 1);
	return (0);
}
