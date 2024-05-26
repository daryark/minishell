/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/24 17:45:07 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_cd(t_mshell *mshell)
{
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	while (mshell->envp[i] && ft_strncmp(mshell->envp[i], "USER=", 5) != 0)
		i++;
	tmp = ft_split(mshell->input, ' ');
	if (tmp[1] == NULL)
	{
		path = ft_strjoin("/home/", mshell->envp[i] + 5);
		chdir(path);
		ft_free(path);
	}
	else
	{
		chdir(tmp[1]);
		ft_free(tmp[1]);
	}
	ft_free(tmp);
}

void	ft_pwd(t_mshell *mshell)
{
	char	*path;

	(void)mshell;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	ft_free(path);
}
