/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:47:29 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/02 19:23:37 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	init_mshell(t_mshell *mshell, char **env)
{
	mshell->env = NULL;
	mshell->export = NULL;
	mshell->exit_status = 0;
	mshell->builtin = NULL;
	mshell->tokarr = NULL;
	mshell->cmdarr = NULL;
	mshell->tokarr_l = 0;
	mshell->cmdarr_l = 0;
	mshell->cmd_num = 0;
	init_env(mshell, env);
	init_builtin_arr(mshell);
}

int	check_input(char *input)
{
	if (!input)
	{
		ft_free(input);
		printf("exit\n");
		exit(0);
	}
	else if (!*input)
	{
		ft_free(input);
		return (1);
	}
	return (0);
}

static void	minishell_loop(t_mshell *mshell)
{
	char	*input;
	char	*path;

	while (1)
	{
		g_signal = 0;
		path = get_currect_path(mshell);
		input = readline(path);
		if (check_input(input))
			continue ;
		add_history(input);
		if (parse_input(input, mshell))
		{
			if (ft_exit(mshell, input))
				continue ;
			execute(mshell);
		}
		clean_command_data(mshell);
		ft_free(input);
	}
	ft_free(path);
}

int	main(int ac, char **av, char **envp)
{
	t_mshell	mshell;

	ft_alloc_init();
	ignore_signals();
	(void)av;
	(void)ac;
	if (ac != 1)
		exit(write(1, RED "No arguments accepted!\n" RE, 32));
	else
	{
		init_mshell(&mshell, get_envp(envp));
		minishell_loop(&mshell);
	}
	ft_destructor();
	return (0);
}
