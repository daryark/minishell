/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:04:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/01 22:59:14 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	return (file);
}

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

void	ft_cd(char *cmd)
{
	char	**tmp_split;
	char	*path;

	tmp_split = ft_split(cmd, ' ');
	if (tmp_split[1] == NULL)
	{
		path = ft_strdup("/home");
		chdir(path);
		free(path);
	}
	else
		chdir(tmp_split[1]);
}

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
