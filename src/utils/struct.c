/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:49:14 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/12 00:09:37 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void    init_mshell(t_mshell *mshell, char **env)
{
    init_env(mshell, env);
    mshell->exit_status = 0;
    mshell->input = NULL;
}
