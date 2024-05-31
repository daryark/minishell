/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/31 16:20:29 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_cd(t_mshell *mshell)
{
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	tmp = mshell->cmdarr[mshell->cmd_num].args;
	if (!tmp[1])
	{
		path = ft_strdup(find_env(mshell->env, "HOME"));
		chdir(path);
		ft_free(path);
	}
	else
		chdir(tmp[1]);
	mshell->exit_status = 0;
}

void	ft_pwd(t_mshell *mshell)
{
	char	*path;

	(void)mshell;
	path = getcwd(NULL, 0);
	if (!path)
		ft_error_exit("pwd: ", strerror(errno), 1);
	printf("%s\n", path);
	ft_free(path);
	mshell->exit_status = 0;
}
