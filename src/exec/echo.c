/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:48:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/01 18:19:18 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

// static void	n_flag(t_cmdarr cmd)
// {
// 	//cut the echo fn
// }

void	ft_echo(t_mshell *mshell)
{
	int	i;
	int	j;
	int	n_line;

	i = 1;
	n_line = 1;
	while (mshell->cmdarr[mshell->cmd_num].args[i])
	{
		if (mshell->cmdarr[mshell->cmd_num].args[i][0] != '-')
			break ;
		j = 1;
		while (mshell->cmdarr[mshell->cmd_num].args[i][j] == 'n')
			j++;
		if (mshell->cmdarr[mshell->cmd_num].args[i][j])
			break ;
		i++;
	}
	if (i > 1)
		n_line = 0;
	while (mshell->cmdarr[mshell->cmd_num].args[i])
	{
		if (mshell->cmdarr[mshell->cmd_num].args[i + 1] != NULL)
			printf("%s ", mshell->cmdarr[mshell->cmd_num].args[i]);
		else
			printf("%s", mshell->cmdarr[mshell->cmd_num].args[i]);
		i++;
	}
	if (n_line)
		printf("\n");
	mshell->exit_status = 0;
}