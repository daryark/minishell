/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_class.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:16:45 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/29 11:57:00 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_class.h"

t_attribute	*attribures(void)
{
	t_attribute	*attributes;

	attributes = malloc(sizeof(t_attribute));
	attributes->name = NULL;
	attributes->type = 0;
	attributes->value.string_value = NULL;
	attributes->value.string_arr_value = NULL;
	attributes->value.args = NULL;
	attributes->next = NULL;
	return (attributes);
}

t_class	*class(void)
{
	t_class	*new_class;

	new_class = malloc(sizeof(t_class));
	new_class->attributes = attribures();
	new_class->attr = attr;
	return (new_class);
}

void	destroy_class(t_class *class)
{
	t_attribute	*attr;
	t_attribute	*next;
	int			i;

	attr = class->attributes;
	while (attr)
	{
		next = attr->next;
		free(attr->name);
		if (attr->type == STR)
			free(attr->value.string_value);
		else if (attr->type == STR_ARR)
		{
			i = 0;
			while (attr->value.string_arr_value[i])
			{
				free(attr->value.string_arr_value[i]);
				i++;
			}
			free(attr->value.string_arr_value);
		}
		free(attr);
		attr = next;
	}
	free(class);
}

size_t	get_arg_size(t_arg *args)
{
	int		i;
	size_t	arg_size;

	i = 0;
	arg_size = 0;
	while (args[i].arg != NULL)
	{
		arg_size += args[i].type;
		i++;
	}
	return (arg_size);
}

void	add_func_args(t_class *class, char *name, t_arg *args)
{
	t_attribute	*attribute;
	int			i;
	size_t		size;
	size_t		current_size;
	size_t		sizes[3];
	int			size_copy;

	attribute = get_attribute(class, name);
	sizes[0] = sizeof(int);
	sizes[1] = sizeof(char *);
	sizes[2] = sizeof(char);
	size = get_arg_size(args);
	i = 0;
	attribute->value.args = malloc(size * sizeof(t_arg));
	size_copy = size;
	size = 0;
	i = 0;
	while (i < size_copy)
	{
		current_size = sizes[i % 3];
		ft_class_memcpy((char *)attribute->value.args + size, &args[i],
			current_size);
		size += current_size;
		i++;
	}
}
