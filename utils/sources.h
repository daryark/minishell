/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sources.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:48:00 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/29 19:00:04 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCES_H
# define SOURCES_H
# include "../minishell.h"

# define RED "\x1b[31m"
# define BLUE "\x1b[34m"
# define RESET "\x1b[0m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *s1, char *s2, int n);
char	**ft_split(char *a, char d);
int		ft_strlen(char *s);
void	ft_strcpy(char *d, char *s);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);

#endif