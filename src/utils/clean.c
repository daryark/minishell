/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:41:07 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/26 17:13:35 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	clean_tokarr(t_token **arr, int *len)
{
	int	i;

	i = -1;
	// printf("%sin clean, len:%d, %s\n", RED, *len, RE);
	while (++i < *len && (*arr) && (*arr)[i].word)
	{
		// printf("i:%i, word:%s\n", i, (*arr)[i].word);
		ft_free((*arr)[i].word);
	}
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
		// printf("before clean, inp_l:%d	", mshell->cmdarr[i].inp_l);
		clean_tokarr(&mshell->cmdarr[i].inp, &mshell->cmdarr[i].inp_l);
		// printf("before clean, out_l:%d	", mshell->cmdarr[i].out_l);
		clean_tokarr(&mshell->cmdarr[i].out, &mshell->cmdarr[i].out_l);
	}
}

void	clean_command_data(t_mshell *mshell)
{
	// printf("before clean, tokarr_l:%d	", mshell->tokarr_l);
	clean_tokarr(&mshell->tokarr, &mshell->tokarr_l);
	clean_cmdarr(mshell);
	//*if we need to clean anything else?
}
