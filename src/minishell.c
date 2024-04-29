/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:23:44 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/30 00:45:15 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_minishell(char **envp)
{
	char	*line;

	while (1)
	{
		line = readline(YELLOW "Minishell$ " RESET);
		if (!line || !ft_strncmp(line, "exit", 4))
			break ;
		printf("line: %s\n", line);
		execute_command(line, envp);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
	{
		printf("Usage: ./minishell\n");
		return (1);
	}
	ft_minishell(envp);
	return (0);
}
