/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:09:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/15 18:54:20 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RE "\033[0m"
# define BLUE "\x1b[34m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"
# define LIGHTGREEN "\x1b[92m"

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include "parsing.h"
# include "execute.h"
# include "sources.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_type
{
	T_WORD = 0,
	T_DQUOTE,
	T_SQUOTE,
	T_PIPE,
	T_LREDIR,
	T_DLREDIR,
	T_RREDIR,
	T_DRREDIR,
	T_CMD,
}				t_type;

typedef struct s_token
{
	char		*word;
	t_type		type; //or char ? '|', '\"', 'w'-for word; 'c' - for cmd...?
}				t_token;

typedef struct s_env_line
{
	char		*val;
	char		*name;
}				t_env_line;

typedef struct s_mshell
{
	t_env_line	*env;
	char		**envp;
	t_token		s_token_arr;
	char		*input;
	int			exit_status;

}				t_mshell;

//*UTILS
// struct.c
void			init_mshell(t_mshell *mshell, char **env);
void			handle_sigint(int signals);
void			ignore_signals(void);

#endif
