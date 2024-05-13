/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:48:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/13 19:05:13 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_echo(t_mshell *mshell)
{
	int		i;
	int		n_flag;
	char	**tmp;

	tmp = ft_split(mshell->input, ' ');
	i = 1;
	n_flag = 0;
	if (tmp[1] && ft_strncmp(tmp[1], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (tmp[i])
	{
		if (tmp[i + 1] != NULL)
			printf("%s ", tmp[i]);
		else
			printf("%s", tmp[i]);
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	ft_free(tmp);
}
