/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:00:05 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/04 18:39:51 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	not_closed_quotes(char *s)
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
		if (arr[i].type == T_PIPE && ((i - 1) < 0 || (i
					+ 1) >= mshell->tokarr_l))
			return (syntax_err(arr[i].word, mshell->exit_status = 2), i);
		else if (arr[i].type > 2 && (i + 1) >= mshell->tokarr_l)
			return (syntax_err("newline", 2), mshell->exit_status = 2);
		else if (arr[i].type > 2 && mshell->tokarr[i + 1].type > 1)
			return (syntax_err(arr[i + 1].word, mshell->exit_status = 2), i);
	}
	return (-1);
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

void	syntax_err(char *s, int status)
{
	printf("minishell: ");
	if (status == 2)
		printf("syntax error near unexpected token `%s'\n", s);
	if (status == 39)
		printf("syntax error unable to locate closing quotation\n");
	if (status == 0)
		printf("warning: shell level (1000) too high, resetting to 1\n");
}

int	input_err_check(t_mshell *mshell, char *input)
{
	int	err_quote;
	int	err_symb;

	err_quote = 0;
	err_symb = 0;
	err_quote = not_closed_quotes(input);
	err_symb = not_valid_symbols(input);
	if (err_quote || err_symb)
	{
		mshell->exit_status = 2;
		if (err_quote)
			syntax_err((char *)&err_quote, 39);
		else if (err_symb)
			syntax_err((char *)&err_symb, mshell->exit_status);	
	}
	else if (empty_str(input))
		mshell->exit_status = 0;
	else
		return (0);
	return (1);
}
