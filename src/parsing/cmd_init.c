/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:14:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/03 16:14:53 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	set_count(t_count *count)
{
	count->arg = 0;
	count->in = 0;
	count->out = 0;
}

void	alloc_cmd(t_count sizes, t_cmdarr *cmd)
{
	cmd->args = ft_malloc(sizeof(char *) * (sizes.arg + 1));
	cmd->inp = ft_malloc(sizeof(t_token) * sizes.in);
	cmd->out = ft_malloc(sizeof(t_token) * sizes.out);
	cmd->args[sizes.arg] = NULL;
	cmd->inp_l = sizes.in;
	cmd->out_l = sizes.out;
}

void	init_cmd(int c, int *t, t_mshell *mshell)
{
	t_count	count;

	set_count(&count);
	while (mshell->tokarr && *t < mshell->tokarr_l && mshell->tokarr[*t].word
		&& mshell->tokarr[*t].type != T_PIPE)
	{
		if (mshell->tokarr[*t].type == T_WORD)
			count.arg++;
		else
		{
			if (mshell->tokarr[*t].type == T_RED_INP
				|| mshell->tokarr[*t].type == T_HEREDOC)
				count.in++;
			else if (mshell->tokarr[*t].type == T_RED_OUT
				|| mshell->tokarr[*t].type == T_APPEND)
				count.out++;
			if (mshell->tokarr[*t].type == T_RED_INP
				&& spec_symb(mshell->tokarr[*t].word) == 2)
				count.out++;
			(*t)++;
		}
		(*t)++;
	}
	alloc_cmd(count, &mshell->cmdarr[c]);
}

void	init_cmdarr(t_mshell *mshell)
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
	mshell->cmdarr_l = c;
	c = -1;
	t = -1;
	while (++c < mshell->cmdarr_l && ++t < mshell->tokarr_l)
		init_cmd(c, &t, mshell);
}
