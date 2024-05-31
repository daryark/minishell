/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:30:39 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/31 14:28:23 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_class.h"

int	ft_class_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	ft_class_strncmp(char *s1, char *s2, size_t n)
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

char	*ft_class_strdup(char *s1)
{
	char	*buffer;
	int		i;

	buffer = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!buffer || !s1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		buffer[i] = s1[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

void	ft_class_memcpy(void *dst, void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
}

void	*attr(t_class *class, char *name)
{
	char	*s;
	char	**arr;
	void	*ret;
	int		i;

	s = get_str(class, name);
	i = get_int(class, name);
	arr = get_arr(class, name);
	if (s)
		ret = &s;
	else if (i)
		ret = &i;
	else if (arr)
		ret = arr;
	else
	{
		call_func(class, name);
		ret = NULL;
	}
	return (ret);
}
