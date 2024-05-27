/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_class.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:12:31 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/26 14:05:59 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLASS_H
# define FT_CLASS_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_class	t_class;
typedef void			(*t_functionpointer)(void *);

typedef enum e_value_type
{
	INT,
	STR,
	STR_ARR,
	FUNC
}						t_value_type;

typedef struct s_value
{
	int					int_value;
	char				*string_value;
	char				**string_arr_value;
	t_functionpointer	function_value;
	void				*args;
	size_t				size;

}						t_value;

typedef struct s_attribute
{
	char				*name;
	t_value_type		type;
	t_value				value;
	struct s_attribute	*next;
}						t_attribute;

typedef struct s_class
{
	t_attribute			*attributes;
	size_t				size;
	void				(*attribute)(t_class *class, char *name,
			t_value_type type, void *value);
	void				*(*get_attribute)(t_class *class, char *name);

}						t_class;

int						ft_class_strncmp(char *s1, char *s2, size_t n);
void					add_args(t_attribute *attribute, void **args);
void					add_attribute(t_class *class, char *name,
							t_value_type type, void *value);
char					**get_string_arr(t_class *class, char *name);
void					*get_attribute(t_class *class, char *name);
void					ft_class_memcpy(void *dst, void *src, size_t n);
void					add_attribute_str(t_class *class, char *name,
							char *value);
void					add_attribute_str_arr(t_class *class, char *name,
							char **value);
void					add_attribute_int(t_class *class, char *name,
							int *value);
void					add_attribute_func(t_class *class, char *name,
							void *value);
char					*get_string(t_class *class, char *name);
void					call_func(t_class *class, char *name);
int						get_int(t_class *class, char *name);
// void					**create_args(int num_args, ...);
void					destroy_class(t_class *class);
int						ft_class_arrlen(char **arr);
char					*ft_class_strdup(char *s1);
int						ft_class_strlen(char *s);
t_class					*class(void);

#endif