/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:02 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/01 13:35:03 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_mshell		t_mshell;
typedef struct s_env_lst	t_env_lst;

typedef						void(exec_fn)(t_mshell *mshell);
typedef struct s_builtin
{
	char					*name;
	exec_fn					*fn_ptr;
}							t_builtin;

void						ft_cd(t_mshell *mshell);
void						ft_env(t_mshell *mshell);
void						ft_pwd(t_mshell *mshell);
void						execute(t_mshell *mshell);
void						ft_echo(t_mshell *mshell);
void						ft_unset(t_mshell *mshell);
void						ft_execve(t_mshell *mshell);
void						ft_export(t_mshell *mshell);
void						tmp_sort_env(t_env_lst *env);
void						ft_execute(t_mshell *mshell);
int							open_file(char *argv, int i);
char						**convert_env(t_env_lst *env);
int							return_builtin_num(char *cmd);
void						wait_in_parent(t_mshell *mshell);
char						*find_env(t_env_lst *env, char *name);
void						heredoc_loop(t_mshell *mshell, int i);
char						*ft_remove_substr(char *str, char *sub);
void						open_input_files(t_mshell *mshell, int i);
void						open_output_files(t_mshell *mshell, int i);
void						open_fds(t_mshell *mshell, int pipes[][2]);
void						remove_one_node(char *str, t_env_lst **env);
void						ft_piping(t_mshell *mshell, int pipes[][2]);
void						close_fds(t_mshell *mshell, int pipes[][2]);

#endif
