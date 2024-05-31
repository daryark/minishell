/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:41:07 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/31 13:18:05 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	clean_tokarr(t_token **arr, int *len)
{
	int	i;

	i = -1;
	while (++i < *len && (*arr) && (*arr)[i].word)
		ft_free((*arr)[i].word);
	if (*len)
		ft_free(*arr);
	*arr = NULL;
	*len = 0;
}

static void	clean_cmdarr(t_mshell *mshell)
{
	int	i;

	i = -1;
	while (++i < mshell->cmdarr_l && mshell->cmdarr)
	{
		ft_free(mshell->cmdarr[i].args);
		clean_tokarr(&mshell->cmdarr[i].inp, &mshell->cmdarr[i].inp_l);
		clean_tokarr(&mshell->cmdarr[i].out, &mshell->cmdarr[i].out_l);
	}
	mshell->cmdarr_l = 0;
}

void	clean_command_data(t_mshell *mshell)
{
	if (mshell->tokarr && mshell->tokarr_l)
		clean_tokarr(&mshell->tokarr, &mshell->tokarr_l);
	if (mshell->cmdarr && mshell->cmdarr_l)
		clean_cmdarr(mshell);
	mshell->cmd_num = 0;
}
