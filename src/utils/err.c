/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:30 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/31 14:33:49 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	alloc_err(void)
{
	exit(printf(RED "Allocation failed\n" RE));
}

void	ft_error_exit(char *str, char *str2, int status)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(2, "minishell: ", 7);
		write(2, str2, ft_strlen(str2));
		exit(1);
	}
	write(2, "minishell: ", 7);
	write(2, str, ft_strlen(str));
	write(2, str2, ft_strlen(str2));
	exit(status);
}
