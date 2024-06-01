/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:48:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/01 22:57:13 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_echo(t_mshell *mshell)
{
	int i;
	int j;
	int n_line;

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