/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:21:52 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/11 02:21:03 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RE "\033[0m"

# include <stdlib.h>
# include <unistd.h>
// # include <dirent.h>
// # include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
// # include <signal.h>
// # include <sys/stat.h>
// # include <sys/types.h>
// # include <sys/wait.h>
# include "../libft/libft.h"
# include "execute.h"
# include "sources.h"

typedef struct	s_env_line
{
	char *name;
	char *val;
}				t_env_line;


typedef struct s_mshell
{
	t_env_line	*env;
	char		*input;

}			   t_mshell;

//*PARSING
// init_env.c
void 	init_env(t_mshell *mshell, char **env);
// parsing.c
void	parse_input(char *input, t_mshell *mshell);
// parse_err.c
int		parse_err(char *input);
//*UTILS
// struct.c
void	init_mshell(t_mshell *mshell, char **env);
// utils_parsing.c
int		arr_len(char **arr);
int		ft_strchr_pos(char *s, int c);
//*EXEC
// execute.c
#endif