/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:24:46 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/12 19:26:15 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	init_mshell(t_mshell *mshell, char **env)
{
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
	// Ctrl+C displays a new prompt on a new line.
	signal(SIGINT, handle_sigint);
	// Ctrl+D exits the program
	signal(SIGQUIT, SIG_IGN);
	// Ctrl+\ does noting
	signal(SIGTERM, SIG_IGN);
}
