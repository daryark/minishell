/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:33:15 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/29 12:01:19 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_class.h"

// for getting attributes from the class by name
void	*get_attribute(t_class *class, char *name)
{
	t_attribute	*attr;

	attr = class->attributes;
	while (attr != NULL)
	{
		if (ft_class_strncmp(attr->name, name, ft_class_strlen(name)) == 0)
			return (attr);
		attr = attr->next;
	}
	write(2, "Attribute not found\n", 21);
	return (NULL);
}

// for getting int attributes from the class
int	get_int(t_class *class, char *name)
{
	t_attribute	*attr;

	attr = get_attribute(class, name);
	if (attr != NULL && attr->type == INT)
		return (attr->value.int_value);
	write(2, "Attribute not found or not of type int\n", 39);
	return (0);
}

// for getting string attributes from the class
char	*get_str(t_class *class, char *name)
{
	t_attribute	*attr;

	attr = get_attribute(class, name);
	if (attr != NULL && attr->type == STR)
		return (attr->value.string_value);
	write(2, "Attribute not found or not of type string\n", 42);
	return (NULL);
}

// for getting string array attributes from the class
char	**get_arr(t_class *class, char *name)
{
	t_attribute	*attr;

	attr = get_attribute(class, name);
	if (attr != NULL && attr->type == STR_ARR)
		return (attr->value.string_arr_value);
	write(2, "Attribute not found or not of type string array\n", 47);
	return (NULL);
}

// for getting function attributes from the class
void	call_func(t_class *class, char *name)
{
	t_attribute	*tmp;

	tmp = class->attributes;
	while (tmp)
	{
		if (ft_class_strncmp(tmp->name, name, ft_class_strlen(name)) == 0)
		{
			if (tmp->type == FUNC)
			{
				tmp->value.function_value(tmp->value.args);
				free(tmp->value.args);
				return ;
			}
		}
		tmp = tmp->next;
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
