/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:09:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/30 15:25:12 by btvildia         ###   ########.fr       */
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

# include "../ft_class/ft_class.h"
# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include "execute.h"
# include "parsing.h"
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

typedef struct s_mshell
{
	t_env_lst	*export;
	t_env_lst	*env;
	t_token		*tokarr;
	t_cmdarr	*cmdarr;
	t_builtin	*builtin;
	int			exit_status;
	int			tokarr_l;
	int			cmdarr_l;
	int			cmd_num;

}				t_mshell;

//*UTILS
void			copy_list(t_env_lst *env, t_env_lst **new);
char			*get_currect_path(t_mshell *mshell);
char			**get_envp(char **envp);
char			*find_path(char *cmd, char *path);
// struct.c
void			init_mshell(t_mshell *mshell, char **env);
void			handle_sigint(int signals);
void			ignore_signals(void);
void			ft_free_array(char **array);
void			alloc_err(void);
char			*arrjoin(char **arr);
char			**split_save_divider(char *s, char c);
int				leave_heredoc(t_mshell *mshell, int err_i);

void			ft_lstadd_env(t_env_lst **lst, char *name, char *val);
void			clean_lst_env(t_env_lst **lst);
void			clean_node_env(t_env_lst **lst);
void			clean_command_data(t_mshell *mshell);
#endif
