/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:09:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/13 22:09:37 by dyarkovs         ###   ########.fr       */
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

typedef struct s_env_line
{
	char		*val;
	char		*name;
}				t_env_line;

typedef struct s_mshell
{
	t_env_line	*env;
	char		*input;
	char		**envp;
	int			exit_status;

}				t_mshell;

//*PARSING
// init_env.c
void			init_env(t_mshell *mshell, char **env);
// parsing.c
int				parse_input(char *input, t_mshell *mshell);
// parse_err.c
void			syntax_err(int c);
int				input_err_check(char *input);
// utils_parsing.c
int				space(char c);
int				arr_len(char **arr);
int				ft_strchr_pos(char *s, int c);
void			quote_opened_type(char c, char *quote);
// dollar_parse.c
void			dollar_question_replace(char **s, int i, t_mshell *mshell);
//*UTILS
// struct.c
void			init_mshell(t_mshell *mshell, char **env);
void			handle_sigint(int signals);
void			ignore_signals(void);

//*EXEC
// execute.c
#endif
