/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:49:14 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/10 03:02:33 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void arr_clean(t_env_line *envp)
{
    while (envp)
    {
        free(envp->name);
        if (envp->val != NULL)
        free(envp->val);
        envp++;
    }
    free(envp);
    envp = NULL;
}

static void init_envp(t_mshell *mshell, char **envp)
{
    int i;
    int divider_pos;
    
    mshell->envp = (t_env_line *)ft_calloc(sizeof(t_env_line *), arr_len(envp));
    if (!mshell->envp)
        exit(printf(RED "Allocation failed\n" RE));
    i = -1;
    while(envp[++i])
    {
        divider_pos = ft_strchr_pos(envp[i], '=');
        // fill_str(str, struct_dest, pos);
        if (divider_pos >= 0)
        {
            mshell->envp[i].name = ft_substr(envp[i], 0, divider_pos - 1);
            mshell->envp[i].val = ft_strdup(&(envp[i][divider_pos]));
        }
        else
        {
            mshell->envp[i].name = ft_strdup((const char *)envp[i]);
            mshell->envp[i].val = NULL;
        }

        if (!mshell->envp[i].val || !mshell->envp[i].name)
        {
            arr_clean(mshell->envp);
            exit(printf(RED "Allocation failed\n" RE));
        }
        // printf("%s%s = %s%s%s\n", YELLOW, mshell->envp[i].name, GREEN, mshell->envp[i].val, RE);.
    }

}

void    init_mshell(t_mshell *mshell, char **envp)
{
    init_envp(mshell, envp);
}
