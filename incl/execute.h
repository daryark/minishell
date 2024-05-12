/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:02 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/12 15:03:30 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_mshell t_mshell;

void	ft_execute(char *line, t_mshell *mshell);
void	ft_execve(char *cmd, char **envp);
void	ft_exec_just_cmd(char *cmd, t_mshell *mshell);
void	ft_cd(char *cmd);
void	ft_echo(char *cmd);
void	ft_pwd(void);
void	ft_env(t_mshell *mshell);

#endif