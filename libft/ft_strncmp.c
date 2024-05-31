/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:58:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/31 14:21:55 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (!s1)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (!s1)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
