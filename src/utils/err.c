/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:30 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/03 18:54:35 by btvildia         ###   ########.fr       */
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
	write(2, "minishell: ", 11);
	if (*str)
	{
		write(2, "`", 1);
		write(2, str, ft_strlen(str));
		write(2, "': ", 2);
	}
	write(2, content, ft_strlen(content));
	write(2, "\n", 1);
	mshell->exit_status = status;
}
