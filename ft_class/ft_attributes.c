/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_attributes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:23:50 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/29 10:16:21 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_class.h"

void	add_attribute_str(t_class *class, char *name, char *value)
{
	t_attribute	*new_attr;

	new_attr = malloc(sizeof(t_attribute));
	new_attr->name = ft_class_strdup(name);
	new_attr->type = STR;
	new_attr->value.string_value = ft_class_strdup(value);
	new_attr->next = class->attributes;
	class->attributes = new_attr;
}

void	add_attribute_str_arr(t_class *class, char *name, char **value)
{
	t_attribute	*new_attr;
	int			i;

	i = 0;
	new_attr = malloc(sizeof(t_attribute));
	new_attr->name = ft_class_strdup(name);
	new_attr->type = STR_ARR;
	new_attr->value.string_arr_value = malloc(sizeof(char *)
			* (ft_class_arrlen(value) + 1));
	while (value[i])
	{
		new_attr->value.string_arr_value[i] = ft_class_strdup(value[i]);
		i++;
	}
	new_attr->value.string_arr_value[i] = NULL;
	new_attr->next = class->attributes;
	class->attributes = new_attr;
}

void	add_attribute_int(t_class *class, char *name, int *value)
{
	t_attribute	*new_attr;

	new_attr = malloc(sizeof(t_attribute));
	new_attr->name = ft_class_strdup(name);
	new_attr->type = INT;
	new_attr->value.int_value = *value;
	new_attr->next = class->attributes;
	class->attributes = new_attr;
}

void	add_attribute_func(t_class *class, char *name, void *value)
{
	t_attribute	*new_attr;

	new_attr = malloc(sizeof(t_attribute));
	new_attr->name = ft_class_strdup(name);
	new_attr->type = FUNC;
	new_attr->value.function_value = value;
	new_attr->next = class->attributes;
	class->attributes = new_attr;
}

void	add(t_class *class, char *name, t_value_type type, void *value)
{
	if (type == STR)
		add_attribute_str(class, name, value);
	else if (type == STR_ARR)
		add_attribute_str_arr(class, name, value);
	else if (type == INT)
		add_attribute_int(class, name, value);
	else if (type == FUNC)
		add_attribute_func(class, name, value);
}
