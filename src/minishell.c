/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:47:29 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/25 17:00:56 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

// n - amnt of fns choice
void	init_builtin_arr(t_mshell *mshell)
{
	int	n_cmds;

	n_cmds = 6;
	mshell->builtin = malloc(sizeof(t_builtin) * n_cmds);
	mshell->builtin[0].name = "pwd";
	mshell->builtin[0].fn_ptr = ft_pwd;
	mshell->builtin[1].name = "cd";
	mshell->builtin[1].fn_ptr = ft_cd;
	mshell->builtin[2].name = "echo";
	mshell->builtin[2].fn_ptr = ft_echo;
	mshell->builtin[3].name = "unset";
	mshell->builtin[3].fn_ptr = ft_unset;
	mshell->builtin[4].name = "export";
	mshell->builtin[4].fn_ptr = ft_export;
	mshell->builtin[5].name = "env";
	mshell->builtin[5].fn_ptr = ft_env;
}

void	init_mshell(t_mshell *mshell, char **env)
{
	mshell->env = NULL;
	mshell->export = 0;
	init_env(mshell, env);
	mshell->envp = env; //*change for get_current_path in minishell_loop fn
	mshell->exit_status = 0;
	mshell->input = NULL; //?*
	mshell->tokarr = NULL;
	mshell->builtin = NULL;
	init_builtin_arr(mshell);
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
			continue ;
		add_history(input);
		if (parse_input(input, mshell))
		{
			ft_free(input);
			continue ;
		}
		ft_execute_with_pipes(mshell);
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
