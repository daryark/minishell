/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 21:18:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/13 15:58:30 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*buffer;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (s_len < start)
	{
		start = 0;
		len = 0;
	}
	if ((s_len - start) < len)
		len = s_len - start;
	buffer = (char *)ft_malloc(sizeof(char) * len + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buffer[i] = s[start + i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_remove_substr(char *str, char *sub)
{
	char	*result;
	char	*found;
	int		len;
	int		new_len;
	int		i;

	result = NULL;
	found = ft_strstr(str, sub);
	if (!str || !sub)
		return (NULL);
	if (found)
	{
		len = ft_strlen(sub);
		new_len = ft_strlen(str) - len;
		result = ft_malloc((new_len + 1) * sizeof(char));
		if (result)
		{
			i = found - str;
			ft_strncpy(result, str, i);
			ft_strncpy(result + i, found + len, new_len - i);
			result[new_len] = '\0';
		}
	}
	return (result);
}
