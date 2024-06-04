/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:15:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/04 18:07:37 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*a;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	a = ft_malloc(i + j + 1);
	if (!a || !s2)
		return (NULL);
	ft_strcpy(a, s1);
	ft_strcpy(a + i, s2);
	return (a);
}
