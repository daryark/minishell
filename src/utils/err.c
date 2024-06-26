/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:30 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/04 14:37:57 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	alloc_err(void)
{
	exit(printf(RED "Allocation failed\n" RE));
}

void	ft_error_exit(char *str, char *str2, int status)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	exit(status);
}

static void	ft_print_err(char *cmd, char *arg, char *content)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write (2, ":", 2);
	if (*arg)
	{
		write(2, "`", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "': ", 2);
	}
	write(2, content, ft_strlen(content));
	write(2, "\n", 1);
}

void	ft_error_return(char *str, t_mshell *mshell, int status, int modif)
{
	char	*name;
	char	*content;

	content = NULL;
	name = mshell->cmdarr[mshell->cmd_num].args[0];
	if (!ft_strcmp(name, "cd") && modif)
		content = "HOME not set";
	else if (!ft_strcmp(name, "cd") && !modif)
		content = "No such file or directory";
	else if (!ft_strcmp(name, "pwd"))
		content = "error retrieving current directory";
	else if (!ft_strcmp(name, "exit") && !modif)
		content = "too many arguments";
	else if (!ft_strcmp(name, "export"))
		content = "not a valid identifier";
	else if (!ft_strcmp(name, "unset"))
		content = "not enough arguments";
	ft_print_err(name, str, content);
	mshell->exit_status = status;
}
