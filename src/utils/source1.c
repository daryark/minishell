/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:49:14 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/30 00:44:50 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/sources.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_strcpy(char *d, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*a;

	i = ft_strlen(s);
	a = malloc(i + 1);
	if (!a)
		return (NULL);
	ft_strcpy(a, s);
	return (a);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*a;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	a = malloc(i + j + 1);
	if (!a || !s1 || !s2)
		return (NULL);
	ft_strcpy(a, s1);
	ft_strcpy(a + i, s2);
	return (a);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s2[i] != '\0' && i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	**ft_put(char **c, char *a, char d)
{
	int	x;
	int	i;
	int	j;

	i = 0;
	j = 0;
	x = 0;
	while (a[i])
	{
		while (a[i] && a[i] == d)
			i++;
		j = i;
		while (a[i] && a[i] != d)
			i++;
		if (i > j)
		{
			c[x] = malloc(sizeof(char) * (i - j) + 1);
			ft_strncpy(c[x], &a[j], i - j);
			x++;
		}
	}
	c[x] = NULL;
	return (c);
}

char	**ft_split(char *a, char d)
{
	int		j;
	int		i;
	char	**c;

	i = 0;
	j = 0;
	while (a[i])
	{
		while (a[i] && a[i] == d)
			i++;
		if (a[i])
			j++;
		while (a[i] && a[i] != d)
			i++;
	}
	c = malloc(sizeof(char *) * (j + 1));
	c = ft_put(c, a, d);
	return (c);
}
