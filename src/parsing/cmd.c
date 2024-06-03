/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:04:49 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/03 15:13:25 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	fill_redir_type(t_token *redir, t_token *tokarr, int *t)
{
	redir->type = tokarr[*t].type;
	(*t)++;
	if (!tokarr[*t].word)
		alloc_err();
	redir->word = ft_strdup(tokarr[*t].word);
}

void	double_redir_case(t_token *redir, t_token *tokarr, int *t)
{
	fill_redir_type(redir, tokarr, t);
	tokarr[--(*t)].type = T_RED_OUT;
}

// takes curr cmd, and token start i for this cmd
// returns token end i (where encounted pipe or end of arr)
void	fill_cmd(int cmd, int *tok, t_mshell *mshell)
{
	int	a;
	int	i;
	int	o;

	a = -1;
	i = -1;
	o = -1;
	while (*tok < mshell->tokarr_l && mshell->tokarr[*tok].type != T_PIPE)
	{
		if (mshell->tokarr[*tok].type == T_RED_INP
			&& spec_symb(mshell->tokarr[*tok].word) == 2)
			double_redir_case(&mshell->cmdarr[cmd].inp[++i], mshell->tokarr,
				tok);
		if (mshell->tokarr[*tok].type == T_RED_INP
			|| mshell->tokarr[*tok].type == T_HEREDOC)
			fill_redir_type(&mshell->cmdarr[cmd].inp[++i], mshell->tokarr, tok);
		else if (mshell->tokarr[*tok].type == T_RED_OUT
			|| mshell->tokarr[*tok].type == T_APPEND)
			fill_redir_type(&mshell->cmdarr[cmd].out[++o], mshell->tokarr, tok);
		else
			mshell->cmdarr[cmd].args[++a] = mshell->tokarr[*tok].word;
		(*tok)++;
	}
}
