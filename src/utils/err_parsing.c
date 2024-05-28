/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:00:05 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/28 16:45:55 by dyarkovs         ###   ########.fr       */
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

int	check_syntax_order(t_mshell *mshell)
{
    int		i;
	t_token	node;

	i = -1;
	while (++i < mshell->tokarr_l)
	{
		node = mshell->tokarr[i];
		if (node.type == T_PIPE)
		{
			if ((i - 1) < 0 || (i + 1) >= mshell->tokarr_l )
				syntax_err(node.word);
		}
			else if (mshell->tokarr)
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

void	syntax_err(int *c)
{
	if (*c == '\'' && !(*c + 1))
	{
		printf("Minishell: syntax error: unable to locate closing quotation\n");
		return ;
	}
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
