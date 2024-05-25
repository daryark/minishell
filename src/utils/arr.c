/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:42:17 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/26 00:13:59 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_free(array[i]);
		i++;
	}
	ft_free(array);
}

char	*arrjoin(char **arr)
{
	int		i;
	char	*res;

	i = -1;
	while (arr[++i])
	{
		if (!i)
			res = ft_strdup(arr[i]);
		if (arr[i + 1])
			res = ft_strjoin(res, arr[i + 1]);
		if (!res)
			alloc_err();
	}
	return (res);
}

void	set_default_arr(t_token *arr, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		arr->word = NULL;
		arr->type = T_NDEF;
	}
}
