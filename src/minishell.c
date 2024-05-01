/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:23:44 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/01 22:52:57 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_minishell(char **envp)
{
	char	*line;
	char	*path;

	while (1)
	{
		path = ft_strjoin(getcwd(NULL, 0), YELLOW "$ " RESET);
		line = readline(path);
		if (!line || !ft_strncmp(line, "exit", 4))
			break ;
		add_history(line);
		parse_cmds(line, envp);
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
