/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/28 17:05:04 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

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

void	ft_execute_with_pipes(t_mshell *mshell)
{
	int		i;
	int		fd[2];
	int		j;
	int		infile;
	int		outfile;
	char	*line;
	char	*limiter;
	int		pid;

	line = NULL;
	limiter = NULL;
	j = 0;
	i = 0;
	infile = 0;
	outfile = 0;
	// print_cmds(mshell);
	// return ;
	while (i < mshell->cmdarr_l) // cmds
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (mshell->cmdarr[i].inp[j].type == T_HEREDOC)
			{
				close(fd[0]);
				limiter = mshell->cmdarr[i].inp[j].word;
				while (1)
				{
					line = readline("heredoc> ");
					if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
					{
						free(line);
						break ;
					}
					write(fd[1], line, ft_strlen(line));
					write(fd[1], "\n", 1);
					free(line);
				}
			}
			if (i != 0)
			{
				dup2(infile, 0);
				close(infile);
			}
			if (i != mshell->cmdarr_l - 1)
				dup2(fd[1], 1);
			close(fd[0]);
			j = 0;
			while (j < mshell->cmdarr[i].out_l)
			{
				if (mshell->cmdarr[i].out[j].type == T_APPEND)
					outfile = open_file(mshell->cmdarr[i].out[j].word, 0);
				else
					outfile = open_file(mshell->cmdarr[i].out[j].word, 1);
				dup2(outfile, 1);
				close(outfile);
				j++;
			}
			j = 0;
			while (j < mshell->cmdarr[i].inp_l)
			{
				infile = open_file(mshell->cmdarr[i].inp[j].word, 2);
				dup2(infile, 0);
				close(infile);
				j++;
			}
			mshell->cmd_num = i;
			ft_execute(mshell);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			if (i != 0)
				close(infile);
			infile = fd[0];
		}
		i++;
	}
}

void	execute(t_mshell *mshell)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	while (mshell->builtin[++i].name && !found)
		found = !ft_strncmp(mshell->builtin[i].name,
				mshell->cmdarr[mshell->cmd_num].args[0],
				ft_strlen(mshell->builtin[i].name));
	if (mshell->cmdarr_l == 1 && found)
	{
		mshell->cmd_num = 0;
		ft_execute(mshell);
	}
	else
		ft_execute_with_pipes(mshell);
}

void	ft_execute(t_mshell *mshell)
{
	int	i;
	int	found;

	found = 0;
	i = -1;
	while (mshell->builtin[++i].name && !found)
		found = !ft_strncmp(mshell->builtin[i].name,
				mshell->cmdarr[mshell->cmd_num].args[0],
				ft_strlen(mshell->builtin[i].name));
	if (!found)
		ft_execve(mshell);
	else
		mshell->builtin[i - 1].fn_ptr(mshell);
}

void	ft_execve(t_mshell *mshell)
{
	char	*path;
	char	**cmds;

	path = NULL;
	cmds = mshell->cmdarr[mshell->cmd_num].args;
	while (mshell->env)
	{
		if (ft_strncmp(mshell->env->name, "PATH", 4) == 0)
			break ;
		mshell->env = mshell->env->next;
	}
	if (ft_strchr(cmds[0], '/') == NULL)
		path = find_path(cmds[0], mshell->env->val);
	else
		path = ft_strdup(cmds[0]);
	if (path == NULL)
	{
		printf("minishell: %s: command not found\n", cmds[0]);
		ft_free_array(cmds);
		exit(127);
	}
	execve(path, cmds, convert_env(mshell->env));
	printf("minishell: %s: command not found\n", cmds[0]);
	ft_free_array(cmds);
	exit(127);
}

char	*find_path(char *cmd, char *path)
{
	char	*c;
	char	*tmp;
	char	**paths;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(path + 5, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		c = ft_strjoin(tmp, cmd);
		ft_free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			ft_free_array(paths);
			return (c);
		}
		free(c);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}
