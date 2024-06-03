/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:54:07 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/03 16:48:39 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../ft_destructor/ft_alloc.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				*ft_itoa(int n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_lstsize(t_list *lst);
int					ft_atoi(char *str);
t_list				*ft_lstnew(void *content);
int					ft_isdigit_loop(char *str);
size_t				ft_strlen(char *str);
char				*ft_strdup(char *s1);
void				ft_bzero(void *s, size_t n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
char				*ft_strchr(char *s, int c);
char				**ft_split(char *s, char c);
char				*ft_strrchr(char *s, int c);
void				*ft_memset(void *b, int c, size_t len);
int					ft_strcmp(char *s1, char *s2);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstadd_front(t_list **lst, t_list *new);
void				*ft_memchr(void *s, int c, size_t n);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char *s1, char *set);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				*ft_memcpy(void *dst, void *src, size_t n);
void				*ft_memmove(void *dst, void *src, size_t len);
int					ft_memcmp(void *s1, void *s2, size_t n);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
char				*ft_strncpy(char *s1, char *s2, int n);
void				ft_strcpy(char *d, char *s);
size_t				ft_strlcat(char *dst, char *src, size_t dstsize);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
char				*ft_substr(char *s, unsigned int start, size_t len);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*ft_strnstr(char *haystack, char *needle, size_t len);
char				*ft_strstr(char *haystack, char *needle);

#endif
