/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:48:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/29 17:31:53 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_echo(t_mshell *mshell)
{
	int		i;
	int		n_flag;
	t_token	*tmp;

	tmp = mshell->tokarr;
	i = 1;
	n_flag = 0;
	if (tmp[1].word && ft_strncmp(tmp[1].word, "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (tmp[i].word && tmp[i].type < 7)
	{
		if (tmp[i + 1].word != NULL)
			printf("%s ", tmp[i].word);
		else
			printf("%s", tmp[i].word);
		i++;
	}
	if (n_flag == 0)
		printf("\n");
}
