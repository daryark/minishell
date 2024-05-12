/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:13:02 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/12 20:13:53 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned int	i;

	a = s;
	c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (a[i] == c)
		{
			return ((void *)&a[i]);
		}
		i++;
	}
	return (NULL);
}
