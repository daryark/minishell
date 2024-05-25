/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:04:49 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/26 00:28:58 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	alloc_cmd_default(int args, int inp, int out, t_cmdarr *cmd)
{
	cmd->args = ft_malloc(sizeof(char *) * (args + 1));
	cmd->inp = ft_malloc(sizeof(t_token) * (inp + 1));
	cmd->out = ft_malloc(sizeof(t_token) * (out + 1));
	if (!cmd->args || !cmd->inp || !cmd->out)
		alloc_err();
	// cmd->args[args] = NULL;
	// set_default_arr(cmd->inp, ++inp);
	// set_default_arr(cmd->out, ++out);
	// cmd->inp[inp].word = NULL;
	// cmd->out[out].word = NULL;
}

static void	init_cmd(int c, int *t, t_mshell *mshell)
{
	int	args;
	int	inp;
	int	out;

	args = 0;
	inp = 0;
	out = 0;
	while (mshell->tokarr[*t].type != T_PIPE
		&& mshell->tokarr[*t].word != NULL)
	{
		// printf("i:%d, word:%s\n", *t, mshell->tokarr[*t].word);
		if (mshell->tokarr[*t].type == T_WORD)
			args++;
		else
		{
			if (mshell->tokarr[*t].type == T_RED_INP
				|| mshell->tokarr[*t].type == T_HEREDOC)
				inp++;
			else if (mshell->tokarr[*t].type == T_RED_OUT
				|| mshell->tokarr[*t].type == T_APPEND)
				out++;
			(*t)++;
		}
		(*t)++;
	}
	// printf("cmd[%d], args:%d, inp%d, out:%d\n", c, args, inp, out);
	alloc_cmd_default(args, inp, out, &mshell->cmdarr[c]);
}

void    init_cmdarr(t_mshell *mshell)
{
	int	c;
	int	t;

	t = -1;
	c = 1;
	while (mshell->tokarr[++t].word != NULL)
	{
		if (mshell->tokarr[t].type == T_PIPE)
			c++;
	}
	mshell->cmdarr = malloc(sizeof(t_cmdarr) * c);
	if (!mshell->cmdarr)
		alloc_err();
	// printf("check len of whole cmdarr:%d\n", len);
	mshell->cmdarr_len = c;
	c = -1;
	t = -1;
	while (++c < mshell->cmdarr_len && mshell->tokarr[++t].word != NULL)
		init_cmd(c, &t, mshell);
}

static void	fill_redir_type(t_token *redir, t_token *tok)
{
	redir->type = tok->type;
	redir->word = (++tok)->word;
}

//takes curr cmd, and token start i for this cmd
//returns token end i (where encounted pipe or end of arr)
int	fill_cmd(t_cmdarr *cmd, t_token *tok)
{
	int	a;
	int	i;
	int	o;
	int	t_i;

	a = -1;
	i = -1;
	o = -1;
	t_i = 0;
	while (tok[t_i].type != T_PIPE
		&& tok[t_i].word != NULL)
	{
		if (tok[t_i].type == T_RED_INP
			|| tok[t_i].type == T_HEREDOC)
			fill_redir_type(&cmd->inp[++i], &tok[t_i++]);
		else if (tok[t_i].type == T_RED_OUT
			|| tok[t_i].type == T_APPEND)
			fill_redir_type(&cmd->out[++o], &tok[t_i++]);
		else
			cmd->args[++a] = tok[t_i].word;
		t_i++;
	}
	cmd->args[++a] = NULL;
	cmd->inp[++i].type = T_NDEF;
	cmd->inp[i].word = NULL;
	cmd->out[++o].type = T_NDEF;
	cmd->out[o].word = NULL;
	return (t_i);
}
