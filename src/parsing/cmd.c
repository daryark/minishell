/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:04:49 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/25 19:33:11 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	alloc_cmd(int args, int inp, int out, t_cmdarr *cmd)
{
	cmd->args = ft_malloc(sizeof(char *) * (args + 1));
	cmd->inp = ft_malloc(sizeof(t_token) * (inp + 1));
	cmd->out = ft_malloc(sizeof(t_token) * (out + 1));
	if (!cmd->args || !cmd->inp || !cmd->out)
		alloc_err();
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
	alloc_cmd(args, inp, out, &mshell->cmdarr[c]);
}

void    init_cmdarr(t_mshell *mshell)
{
	int	c;
	int	t;
	int	len;

	t = -1;
	len = 1;
	while (mshell->tokarr[++t].word != NULL)
	{
		if (mshell->tokarr[t].type == T_PIPE)
			len++;
	}
	mshell->cmdarr = malloc(sizeof(t_cmdarr) * len);
	if (!mshell->cmdarr)
		alloc_err();
	// printf("check len of whole cmdarr:%d\n", len);
	mshell->cmdarr_len = len;
	c = -1;
	t = -1;
	while (++c < mshell->cmdarr_len && mshell->tokarr[++t].word != NULL)
		init_cmd(c, &t, mshell);
}
