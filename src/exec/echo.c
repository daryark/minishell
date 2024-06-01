/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:48:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/01 17:11:05 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_echo(t_mshell *mshell)
{
	int	i;
	int	n_line;

	i = 1;
	n_line = 1;
	// while (mshell->cmdarr[mshell->cmd_num].args[i]
	// 	&& !ft_strncmp(mshell->cmdarr[mshell->cmd_num].args[i], "-n", 3))
	// 	i++;
	// if (i > 1)
	// 	n_line = 0;
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

// while (mshell->cmdarr[mshell->cmd_num].args[i])
// 	{
// 		if (mshell->cmdarr[mshell->cmd_num].args[i][0] != '-')
// 			break ;
// 		if (!ft_memchr(&mshell->cmdarr[mshell->cmd_num].args[i][1], 'n',
// 			ft_strlen(mshell->cmdarr[mshell->cmd_num].args[i]) - 1))
// 			break ;
// 		i++;
// 	}
// 	if (i > 1)
// 		n_line = 0;