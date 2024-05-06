/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:23:44 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/06 20:45:36 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)envp;
	if (ac != 1)
		exit(write(1, RED "No arguments accepted!\n" RE, 32));
	else
		write(1, GREEN "OK\n" RE, 14);
	return (0);
}
