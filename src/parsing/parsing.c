/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:04:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/04/30 22:58:06 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_execute_with_pipes(char *cmd, char **envp);

void	parse_for_input_output(char *cmd, char **envp)
{
	char	*input;
	char	*output;
	char	**split;
	int		i;

	i = 0;
	(void)envp;
	input = NULL;
	output = NULL;
	split = ft_split(cmd, ' ');
	while (split[i] != NULL)
	{
		if (ft_strncmp(split[i], "<", 1) == 0)
			input = split[i + 1];
		if (ft_strncmp(split[i], ">", 1) == 0)
			output = split[i + 1];
		i++;
	}
}

void	parse_cmds(char *cmd, char **envp)
{
	char	**cmds;

	cmds = ft_split(cmd, '|');
	if (ft_strchr(cmd, '<') || ft_strchr(cmd, '>'))
		parse_for_input_output(cmd, envp);
	ft_execute_with_pipes(cmd, envp);
}

void	ft_execute_with_pipes(char *cmd, char **envp)
{
	int i;
	char **cmds;
	int fd[2];
	int fd_in;

	i = 0;
	cmds = ft_split(cmd, '|');
	while (cmds[i] != NULL)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(fd_in, 0);
			if (cmds[i + 1] != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			ft_execve(cmds[i], envp);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fd_in = fd[0];
		}
		i++;
	}
}