/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:09:10 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/28 13:32:59 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*get_currect_path(t_mshell *mshell)
{
	static char	*path;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	while (mshell->env)
	{
		if (!ft_strncmp(mshell->env->name, "USER", 5))
			break ;
		mshell->env = mshell->env->next;
	}
	tmp3 = getcwd(NULL, 0);
	if (!tmp3)
	{
		printf("\nyou can use only 'cd ..' or 'exit'\n\n");
		return (path);
	}
	tmp = ft_strjoin("/home/", mshell->env->val);
	tmp2 = ft_strjoin(ft_remove_substr(tmp3, tmp), "$ ");
	ft_free(tmp3);
	path = ft_strjoin(YELLOW "Minishell~" RE, tmp2);
	ft_free(tmp2);
	return (path);
}
