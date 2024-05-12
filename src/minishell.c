/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:47:29 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/12 15:51:54 by btvildia         ###   ########.fr       */
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
	path = ft_strjoin(LIGHTGREEN "Minishell~" RE, tmp2);
	free(tmp2);
	return (path);
}

static void	minishell_loop(t_mshell *mshell)
{
	char	*input;
	char	*path;

	while (1)
	{
		path = get_currect_path();
		input = readline(path);
		if (!input || *input == '\0')
		{
			printf("Exiting...\n");
			// free(input);
			continue ;
		}
		add_history(input);
		if (!input || ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		parse_input(input, mshell);
		ft_execute(input, mshell);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_mshell	mshell;

	(void)av;
	if (ac != 1)
		exit(write(1, RED "No arguments accepted!\n" RE, 32));
	else
	{
		write(1, GREEN "OK\n" RE, 14);
		init_mshell(&mshell, envp);
		minishell_loop(&mshell);
	}
	return (0);
}
