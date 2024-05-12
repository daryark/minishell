/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:23:44 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/12 13:33:47 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*get_currect_path(void)
{
	char	*path;
	char	*tmp;
	char	*tmp2;

	tmp = getcwd(NULL, 0);
	tmp2 = ft_strjoin(tmp, "$ ");
	free(tmp);
	path = ft_strjoin(LIGHTGREEN "Minishell~" RESET, tmp2);
	free(tmp2);
	return (path);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*path;

	(void)argc;
	(void)argv;
	// t_args	args;
	while (1)
	{
		path = get_currect_path();
		line = readline(path);
		if (!line || ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		add_history(line);
		// ft_parse(&args, line); // we will parse the arguments
		// ft_execute(&args);
		// and when we have the arguments we will execute them
		ft_execute(line, envp);
		free(line);
	}
	return (0);
}
