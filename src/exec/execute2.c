/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:58:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/02 12:04:43 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// ft_cd() is a function that changes the current working directory

void	ft_cd(char *cmd)
{
	char	**tmp_split;
	char	*path;

	tmp_split = ft_split(cmd, ' ');
	if (tmp_split[1] == NULL)
	{
		path = ft_strdup("/home");
		chdir(path);
		free(path);
	}
	else
		chdir(tmp_split[1]);
}
