/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:02 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/25 20:26:54 by btvildia         ###   ########.fr       */
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
void						ft_echo(t_mshell *mshell);
void						ft_unset(t_mshell *mshell);
void						ft_export(t_mshell *mshell);
void						ft_execute(t_mshell *mshell, char **cmds);
void						ft_execve(char **cmds, char **envp);
char						*find_path(char *cmd, char *path);
void						ft_execute_with_pipes(t_mshell *mshell);
char						*ft_remove_substr(char *str, char *sub);

#endif
