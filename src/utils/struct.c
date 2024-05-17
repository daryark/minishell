/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:24:46 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/17 14:32:10 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	init_mshell(t_mshell *mshell, char **env)
{
	mshell->env = NULL;
	init_env(mshell, env);
	mshell->envp = env;

	mshell->exit_status = 0;
	mshell->input = NULL;
}


void	handle_sigint(int signals)
{
	(void)signals;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ignore_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
