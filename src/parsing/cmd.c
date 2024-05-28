/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:04:49 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/28 21:24:50 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	alloc_cmd(int args, int inp, int out, t_cmdarr *cmd)
{
	cmd->args = ft_malloc(sizeof(char *) * (args + 1));
	cmd->inp = ft_malloc(sizeof(t_token) * inp);
	cmd->out = ft_malloc(sizeof(t_token) * out);
	if (!cmd->args || !cmd->inp || !cmd->out)
		alloc_err();
	cmd->args[args] = NULL;
	cmd->inp_l = inp;
	cmd->out_l = out;
}

static void	init_cmd(int c, int *t, t_mshell *mshell)
{
	int	args;
	int	inp;
	int	out;

	args = 0;
	inp = 0;
	out = 0;
	// printf("%sinit cmd, *t:%d, cmd:%d	%s", RED, *t, c, RE);
	while (mshell->tokarr && *t < mshell->tokarr_l && mshell->tokarr[*t].word
		&& mshell->tokarr[*t].type != T_PIPE)
	{
		// printf("i:%d, word:%s\n", *t, mshell->tokarr[*t].word);
		if (mshell->tokarr[*t].type == T_WORD)
			args++;
		else
		{
			if (mshell->tokarr[*t].type == T_RED_INP && spec_symb(mshell->tokarr[*t].word) == 2)
			{
				inp++;
				out++;
			}
			else if (mshell->tokarr[*t].type == T_RED_INP
				|| mshell->tokarr[*t].type == T_HEREDOC)
				inp++;
			else if (mshell->tokarr[*t].type == T_RED_OUT
				|| mshell->tokarr[*t].type == T_APPEND)
				out++;
			(*t)++;
		}
		(*t)++;
	}
	printf("cmd[%d], args:%d, inp%d, out:%d\n", c, args, inp, out);
	alloc_cmd(args, inp, out, &mshell->cmdarr[c]);
}

void    init_cmdarr(t_mshell *mshell)
{
	int	c;
	int	t;

	t = -1;
	c = 1;
	while (++t < mshell->tokarr_l)
	{
		if (mshell->tokarr[t].type == T_PIPE)
			c++;
	}
	mshell->cmdarr = ft_malloc(sizeof(t_cmdarr) * c);
	if (!mshell->cmdarr)
		alloc_err();
	mshell->cmdarr_l = c;
	c = -1;
	t = -1;
	while (++c < mshell->cmdarr_l && ++t < mshell->tokarr_l)
		init_cmd(c, &t, mshell);
}

void	fill_redir_type(t_token *redir, t_token *tokarr, int *t)
{
	redir->type = tokarr[*t].type;
	(*t)++;
	if (!tokarr[*t].word)
		alloc_err();
	redir->word = ft_strdup(tokarr[*t].word);
	// printf("%sredir->word:%s%s	", RED, redir->word, RE);
}

void	double_redir_case(t_token *redir, t_token *tokarr, int *t)
{
	fill_redir_type(redir, tokarr, t);
	tokarr[--(*t)].type = T_RED_OUT;
}

//takes curr cmd, and token start i for this cmd
//returns token end i (where encounted pipe or end of arr)
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
		if (mshell->tokarr[*tok].type == T_RED_INP && \
		spec_symb(mshell->tokarr[*tok].word) == 2)
			double_redir_case(&mshell->cmdarr[cmd].inp[++i],  mshell->tokarr, tok);
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
