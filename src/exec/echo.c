/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:48:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/30 21:27:42 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_echo(t_mshell *mshell)
{
	int	i;
	int	n_line;

	i = 1;
	n_line = 1;
	if (mshell->cmdarr[mshell->cmd_num].args[1]
		&& !ft_strncmp(mshell->cmdarr[mshell->cmd_num].args[1], "-n", 3))
	{
		n_line = 0;
		i++;
	}
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
}
