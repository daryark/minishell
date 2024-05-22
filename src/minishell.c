/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:47:29 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/22 16:05:07 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	init_mshell(t_mshell *mshell, char **env)
{
	mshell->env = NULL;
	init_env(mshell, env);
	mshell->envp = env;
	mshell->exit_status = 0;
	mshell->input = NULL;
}

char	*get_currect_path(char **envp)
{
	static char	*path;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;
	int			i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "USER=", 5) != 0)
		i++;
	tmp3 = getcwd(NULL, 0);
	if (!tmp3)
	{
		printf("\nyou can use only 'cd ..' or 'exit'\n\n");
		return (path);
	}
	tmp = ft_strjoin("/home/", envp[i] + 5);
	tmp2 = ft_strjoin(ft_remove_substr(tmp3, tmp), "$ ");
	ft_free(tmp3);
	path = ft_strjoin(YELLOW "Minishell~" RE, tmp2);
	ft_free(tmp2);
	return (path);
}

static void	minishell_loop(t_mshell *mshell)
{
	char	*input;
	char	*path;

	ignore_signals();
	while (1)
	{
		path = get_currect_path(mshell->envp);
		input = readline(path);
		if (!input || (!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4))
		{
			printf("exit\n");
			ft_free(input);
			break ;
		}
		if (!*input)
		{
			ft_free(input);
			continue ;
		}
		add_history(input);
		if (parse_input(input, mshell))
		{
			ft_free(input);
			continue ;
		}
		ft_execute(mshell);
		ft_free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_mshell	mshell;

	ft_alloc_init();
	(void)av;
	(void)ac;
	if (ac != 1)
		exit(write(1, RED "No arguments accepted!\n" RE, 32));
	else
	{
		write(1, GREEN "OK\n" RE, 14);
		init_mshell(&mshell, envp);
		minishell_loop(&mshell);
	}
	ft_destructor();
	return (0);
}
