/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:02 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/02 19:38:39 by btvildia         ###   ########.fr       */
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

// builtins
void						ft_cd(t_mshell *mshell);
void						ft_env(t_mshell *mshell);
void						ft_pwd(t_mshell *mshell);
void						ft_echo(t_mshell *mshell);
void						ft_unset(t_mshell *mshell);
void						ft_execve(t_mshell *mshell);
void						ft_export(t_mshell *mshell);
void						init_builtin_arr(t_mshell *mshell);
int							ft_exit(t_mshell *mshell, char *input);

// execute
void						execute(t_mshell *mshell);
void						ft_execute(t_mshell *mshell);
int							open_file(char *argv, int i);
void						heredoc_loop(t_mshell *mshell, int i);
void						heredoc(t_mshell *mshell, int i, int j);
void						ft_piping(t_mshell *mshell, int **pipes);
void						open_input_files(t_mshell *mshell, int i);
void						open_output_files(t_mshell *mshell, int i);

#endif
