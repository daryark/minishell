/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:48:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/15 14:53:13 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	handle_dollar_sign(t_mshell *mshell, char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) == 1)
	{
		printf("$ ");
		return ;
	}
	else if (ft_strlen(name) == 2)
	{
		if (name[1] == '?')
			printf("%d", mshell->exit_status);
		else if (name[1] == '$')
			printf("%d", getpid());
		else
			printf("$ ");
	}
	while (mshell->env[i].name)
	{
		if (ft_strncmp(mshell->env[i].name, name + 1, ft_strlen(name) - 1) == 0)
		{
			printf("%s", mshell->env[i].val);
			return ;
		}
		i++;
	}
}

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
		if (ft_strchr(tmp[i], '$') != NULL)
			handle_dollar_sign(mshell, tmp[i]);
		else if (tmp[i + 1] != NULL)
			printf("%s ", tmp[i]);
		else
			printf("%s", tmp[i]);
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	ft_free(tmp);
}
