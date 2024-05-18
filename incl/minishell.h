/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:09:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/18 18:38:21 by dyarkovs         ###   ########.fr       */
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



//*UTILS
// struct.c
void			init_mshell(t_mshell *mshell, char **env);
void			handle_sigint(int signals);
void			ignore_signals(void);
int	            empty_str(char *s);
void            alloc_err(void);
char			**split_save_divider(char *s, char c);

void	        ft_lstadd_env(t_env_lst **lst, char *name, char *val);
void	        clean_lst_env(t_env_lst **lst);
void	        clean_node_env(t_env_lst **lst);
#endif
