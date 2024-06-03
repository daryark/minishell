/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:48:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/03 16:23:50 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

static int	handle_n_flag(t_mshell *mshell, int *n_line)
{
	int	i;
	int	j;

	i = 1;
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
		*n_line = 0;
	else
		*n_line = 1;
	return (i);
}

void	ft_echo(t_mshell *mshell)
{
	int	i;
	int	n_line;

	i = handle_n_flag(mshell, &n_line);
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
