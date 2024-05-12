/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:24:46 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/12 14:38:53 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void    init_mshell(t_mshell *mshell, char **env)
{
    init_env(mshell, env);
	mshell->envp = env;
    mshell->exit_status = 0;
    mshell->input = NULL;
}

void	ft_strncpy(char *d, char *s, int n)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && i < n)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

void	ft_strcpy(char *d, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}
