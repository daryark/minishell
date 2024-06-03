/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:09:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/03 17:36:27 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RE "\001\033[0m\002"
# define RED "\001\033[1;31m\002"
# define BLUE "\001\033[1;34m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define MAGENTA "\001\033[0;35m\002"
# define LIGHTGREEN "\001\033[1;32m\002"

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include "execute.h"
# include "parsing.h"
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

extern int		g_signal;

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
void			ignore_signals(void);
char			**get_envp(char **envp);
void			child_signal(int signal);
void			handle_sigint(int signals);
void			tmp_sort_env(t_env_lst *env);
int				return_builtin_num(char *cmd);
char			**convert_env(t_env_lst *env);
void			wait_in_parent(t_mshell *mshell);
char			*find_path(char *cmd, char *path);
char			*get_currect_path(t_mshell *mshell);
char			*find_env(t_env_lst *env, char *name);
char			*ft_remove_substr(char *str, char *sub);
void			open_fds(t_mshell *mshell, int **pipes);
void			close_fds(t_mshell *mshell, int **pipes);
void			copy_list(t_env_lst *env, t_env_lst **new);
void			remove_one_node(char *str, t_env_lst **env);
void			ft_error_exit(char *str, char *str2, int status);
void			export_loop(t_mshell *mshell, char **args, int i);
void			ft_error_return(char *str, t_mshell *mshell, int status, \
				int modif);
	// struct.c
void			alloc_err(void);
int				empty_str(char *s);
char			*arrjoin(char **arr);
void			ft_free_array(char **array);
void			clean_lst_env(t_env_lst **lst);
void			clean_node_env(t_env_lst **lst);
void			clean_command_data(t_mshell *mshell);
char			**split_save_divider(char *s, char c);
void			init_mshell(t_mshell *mshell, char **env);
int				leave_heredoc(t_mshell *mshell, int err_i);
void			ft_lstadd_env(t_env_lst **lst, char *name, char *val);
#endif
