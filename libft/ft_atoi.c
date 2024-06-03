/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:59:34 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/03 16:49:03 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	long	i;
	long	x;
	int		s;

	i = 0;
	x = 0;
	s = 1;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n'))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		x = x * 10 + (str[i] - '0');
		i++;
	}
	if (x > 2147483648)
		return (0);
	return (x * s);
}
