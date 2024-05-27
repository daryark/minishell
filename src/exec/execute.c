/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/27 13:37:20 by btvildia         ###   ########.fr       */
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
	int		infile;
	int		outfile;
	int		status;
	char	*line;
	char	*limiter;
	pid_t	pid;
	int		j;

	limiter = NULL;
	line = NULL;
	j = 0;
	i = 0;
	infile = 0;
	outfile = 0;
	status = 0;
	// print_cmds(mshell);
	// return ;
	while (i < mshell->cmdarr_l) // cmds
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
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
				if (mshell->cmdarr[i].inp[j].type == T_HEREDOC)
				{
					close(fd[0]);
					limiter = mshell->cmdarr[i].inp[j].word;
					while (1)
					{
						line = readline("heredoc> ");
						if (!line || ft_strncmp(line, limiter,
								ft_strlen(limiter)) == 0)
						{
							free(line);
							break ;
						}
						write(fd[1], line, ft_strlen(line));
						write(fd[1], "\n", 1);
						free(line);
					}
				}
				else
					infile = open_file(mshell->cmdarr[i].inp[j].word, 2);
				dup2(infile, 0);
				close(infile);
				j++;
			}
			ft_execute(mshell, mshell->cmdarr[i].args);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			close(fd[1]);
			infile = fd[0];
		}
		i++;
	}
}

void	ft_execute(t_mshell *mshell, char **cmds)
{
	// int	i;
	// int	found;
	// found = 0;
	// i = -1;
	// while (mshell->builtin[++i].name && !found)
	// 	found = !ft_strncmp(mshell->builtin[i].name, mshell->tokarr[0].word,
	// 			ft_strlen(mshell->builtin[i].name))
	// 		&& !ft_strncmp(mshell->builtin[i].name, mshell->tokarr[0].word,
	// 			ft_strlen(mshell->tokarr[0].word));
	// if (!found)
	//
	ft_execve(cmds, mshell->envp);
	// else
	// 	mshell->builtin[i - 1].fn_ptr(mshell);
}

void	ft_execve(char **cmds, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (ft_strchr(cmds[0], '/') == NULL)
		path = find_path(cmds[0], envp[i]);
	else
		path = ft_strdup(cmds[0]);
	if (path == NULL)
	{
		printf("minishell: %s: command not found\n", cmds[0]);
		ft_free_array(cmds);
		exit(127);
	}
	execve(path, cmds, envp);
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
