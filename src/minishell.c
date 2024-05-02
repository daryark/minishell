/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:23:44 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/02 11:53:56 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

// ft_get_user() is a function that returns the username from the environment

char	*ft_get_user(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "USER=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

// get_path() is a function that returns the current working directory, without
// "/home/user/" at the beginning of the path.

char	*get_currect_path(char **envp)
{
	char	*user;
	char	*path;
	char	*tmp;

	user = ft_strjoin("/home/", ft_get_user(envp));
	tmp = ft_strjoin(ft_remove_substr(getcwd(NULL, 0), user),
			YELLOW "$ " RESET);
	path = ft_strjoin(YELLOW "Minishell~" RESET, tmp);
	free(user);
	free(tmp);
	return (path);
}

void	ft_minishell(char **envp)
{
	char	*line;
	char	*path;

	while (1)
	{
		path = get_path(envp);
		line = readline(path);
		if (!line || !ft_strncmp(line, "exit", 4))
			break ;
		add_history(line);
		parse_cmds(line, envp);
		free(path);
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
