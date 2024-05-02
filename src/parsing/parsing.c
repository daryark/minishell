/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:04:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/02 12:05:00 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// ft_remove_substr() is a function that removes a substring from a string
// init_args() is a function that initializes the t_args structure

void	init_args(t_args *args, char *cmd, char **envp)
{
	char	**tmp_split;
	int		i;

	args->input = NULL;
	args->output = NULL;
	args->cmds = NULL;
	args->pipes = 0;
	args->envp = envp;
	i = 0;
	tmp_split = ft_split(cmd, ' ');
	// This while loop checks if there is an input or output redirection
	while (tmp_split[i] != NULL)
	{
		if (ft_strncmp(tmp_split[i], "|", 1) == 0)
			args->pipes++;
		if (ft_strncmp(tmp_split[i], "<", 1) == 0)
			args->input = tmp_split[i + 1];
		if (ft_strncmp(tmp_split[i], ">", 1) == 0)
			args->output = tmp_split[i + 1];
		i++;
	}
	// If there is an input or output redirection,
	// the file is opened and put in args->infile or args->outfile
	if (args->input)
	{
		args->infile = open_file(args->input, 2);
		cmd = ft_remove_substr(cmd, "<");
		cmd = ft_remove_substr(cmd, args->input);
	}
	if (args->output)
	{
		args->outfile = open_file(args->output, 1);
		cmd = ft_remove_substr(cmd, ">");
		cmd = ft_remove_substr(cmd, args->output);
	}
	args->cmds = ft_split(cmd, '|');
}

// parse_cmds() is a function that parses the commands and executes them
void	parse_cmds(char *cmd, char **envp)
{
	t_args	args;

	init_args(&args, cmd, envp);
	if (ft_strncmp(cmd, "cd", 2) == 0)
	{
		ft_cd(cmd);
		return ;
	}
	/*
		else if (ft_strncmp(cmd, "echo", 4) == 0)
			ft_echo(cmd);
		else if (ft_strncmp(cmd, "pwd", 3) == 0)
			ft_pwd();
		else if (ft_strncmp(cmd, "export", 6) == 0)
			ft_export(cmd);
		else if (ft_strncmp(cmd, "unset", 5) == 0)
			ft_unset(cmd);
		else if (ft_strncmp(cmd, "env", 3) == 0)
			ft_env(envp);
	*/
	if (!args.input && !args.output)
		execute_just_pipes(args.cmds, envp);
	else
		execute_infile_outfile(args);
}
