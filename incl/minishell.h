/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:21:52 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/01 20:25:28 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "execute.h"
# include "sources.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	char	*input;
	char	*output;
	int		infile;
	int		outfile;
	char	**cmds;
	int		pipes;
	char	**envp;
}			t_args;

void		ft_minishell(char **envp);
void		parse_cmds(char *cmd, char **envp);

#endif