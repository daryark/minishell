/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:49:14 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/02 12:07:21 by btvildia         ###   ########.fr       */
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

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
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

int	ft_strncmp(char *s1, char *s2, size_t n)
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*a;

	i = 0;
	j = ft_strlen(s);
	if (start >= j)
	{
		start = 0;
		len = 0;
	}
	if (len > j - start)
		len = j - start;
	a = malloc(len + 1);
	if (!a)
		return (NULL);
	while (i < len)
	{
		a[i] = s[start + i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_strtrim(char *s1, char *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*a;

	a = 0;
	if (!s1 || !set)
		return (a);
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (j > i && s1[j - 1] && ft_strchr(set, s1[j - 1]))
			j--;
		a = (char *)malloc(sizeof(char) * (j - i + 1));
		if (!a)
			return (NULL);
		ft_strncpy(a, s1 + i, j - i);
	}
	return (a);
}

char	*ft_strstr(char *haystack, char *needle)
{
	size_t	len;

	len = ft_strlen(needle);
	if (len == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		if (ft_strncmp(haystack, needle, len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

// ft_remove_substr() is a function that removes a substring from a string
// example: ft_remove_substr("Hello World", "World") returns "Hello "

char	*ft_remove_substr(char *str, char *substr)
{
	char	*result;
	char	*found;
	int		len;
	int		new_len;
	int		i;

	result = NULL;
	if (str && substr)
	{
		found = ft_strstr(str, substr);
		if (found)
		{
			len = ft_strlen(substr);
			new_len = ft_strlen(str) - len;
			result = (char *)malloc((new_len + 1) * sizeof(char));
			if (result)
			{
				i = found - str;
				ft_strncpy(result, str, i);
				ft_strncpy(result + i, found + len, new_len - i);
				result[new_len] = '\0';
			}
		}
		else
		{
			result = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
			if (result)
				ft_strncpy(result, str, ft_strlen(str) + 1);
		}
	}
	return (result);
}
