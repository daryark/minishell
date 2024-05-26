/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/26 17:50:13 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

int	count_pipes(t_mshell *mshell)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (mshell->tokarr[i].type > 0 && mshell->tokarr[i].type < 7)
	{
		if (mshell->tokarr[i].type == T_PIPE)
			pipes++;
		i++;
	}
	return (pipes);
}

char	**get_only_files(t_mshell *mshell, int file)
{
	int		i;
	int		j;
	int		k;
	char	**tmp_join;

	i = 0;
	j = 0;
	k = 0;
	tmp_join = ft_malloc(sizeof(char *) * (mshell->tokarr_l + 1));
	while (i < mshell->tokarr_l)
	{
		if (mshell->tokarr[i].type == T_RED_OUT && file == 0)
		{
			tmp_join[j] = ft_strdup(mshell->tokarr[i + 1].word);
			j++;
		}
		else if (mshell->tokarr[i].type == T_RED_INP && file == 1)
		{
			tmp_join[j] = ft_strdup(mshell->tokarr[i + 1].word);
			j++;
		}
		i++;
	}
	return (tmp_join);
}

char	**get_only_words(t_mshell *mshell, int i)
{
	int		j;
	int		k;
	char	**tmp_join;
	int		pipes_passed;

	pipes_passed = 0;
	j = 0;
	k = 0;
	tmp_join = ft_malloc(sizeof(char *) * (mshell->tokarr_l + 1));
	while (k < mshell->tokarr_l)
	{
		if (mshell->tokarr[k].type == T_PIPE)
			pipes_passed++;
		if (pipes_passed == i)
		{
			if (i != 0)
				k++;
			while (mshell->tokarr[k].type > 0 && mshell->tokarr[k].type < 7)
			{
				if (mshell->tokarr[k].type == T_WORD)
				{
					tmp_join[j] = ft_strdup(mshell->tokarr[k].word);
					j++;
				}
				if (mshell->tokarr[k].type != T_WORD)
					return (tmp_join);
				k++;
			}
		}
		k++;
	}
	tmp_join[j] = NULL;
	return (tmp_join);
}

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
	int		pipes;
	int		status;
	char	**tmp_join;
	char	**infiles;
	char	**outfiles;
	pid_t	pid;
	int		j;

	j = 0;
	i = 0;
	pipes = 0;
	infile = 0;
	outfile = 0;
	status = 0;
	pipes = count_pipes(mshell);
	// read from
	infiles = get_only_files(mshell, 1);
	// read to
	outfiles = get_only_files(mshell, 0);
	while (i < pipes + 1)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			tmp_join = get_only_words(mshell, i);
			if (i != 0)
			{
				dup2(infile, 0);
				close(infile);
			}
			if (i != pipes)
				dup2(fd[1], 1);
			close(fd[0]);
			j = 0;
			while (infiles[j] != NULL)
			{
				infile = open_file(infiles[j], 2);
				dup2(infile, 0);
				close(infile);
				j++;
			}
			j = 0;
			while (outfiles[j] != NULL)
			{
				outfile = open_file(outfiles[j], 1);
				dup2(outfile, 1);
				close(outfile);
				j++;
			}
			ft_execute(mshell, tmp_join);
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
