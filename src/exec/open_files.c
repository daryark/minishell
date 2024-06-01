/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:42:47 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/01 13:00:52 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0644);
	else if (i == 3)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
		ft_error_exit(argv, ": No such file or directory\n", 1);
	return (file);
}

void	heredoc(t_mshell *mshell, int i, int j)
{
	char	*line;
	char	*limiter;
	int		tmp_fd;

	limiter = mshell->cmdarr[i].inp[j].word;
	tmp_fd = open_file("/tmp/heredoc_tmp", 3);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
}

void	heredoc_loop(t_mshell *mshell, int i)
{
	int	j;

	j = 0;
	signal(SIGINT, heredoc_signal);
	while (j < mshell->cmdarr[i].inp_l)
	{
		if (mshell->cmdarr[i].inp[j].type == T_HEREDOC)
			heredoc(mshell, i, j);
		j++;
	}
}

void	open_input_files(t_mshell *mshell, int i)
{
	int	j;
	int	file;

	j = 0;
	while (j < mshell->cmdarr[i].inp_l)
	{
		if (mshell->cmdarr[i].inp[j].type == T_HEREDOC)
			file = open_file("/tmp/heredoc_tmp", 2);
		else
			file = open_file(mshell->cmdarr[i].inp[j].word, 2);
		dup2(file, 0);
		close(file);
		j++;
	}
}
void	open_output_files(t_mshell *mshell, int i)
{
	int	j;
	int	file;

	j = 0;
	while (j < mshell->cmdarr[i].out_l)
	{
		if (mshell->cmdarr[i].out[j].type == T_APPEND)
			file = open_file(mshell->cmdarr[i].out[j].word, 0);
		else
			file = open_file(mshell->cmdarr[i].out[j].word, 1);
		dup2(file, 1);
		close(file);
		j++;
	}
}
