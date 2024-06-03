/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 01:00:02 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/03 16:15:07 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	env_lst_len(t_env_lst *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void	ft_lstadd_env(t_env_lst **lst, char *name, char *val)
{
	t_env_lst	*node;
	t_env_lst	*head;

	node = ft_malloc(sizeof(t_env_lst));
	head = *lst;
	if (!head)
		*lst = node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	node->name = name;
	node->val = val;
	node->next = NULL;
}

void	clean_node_env(t_env_lst **lst)
{
	t_env_lst	*tmp;

	tmp = (*lst)->next;
	ft_free((*lst)->name);
	if ((*lst)->val)
		ft_free((*lst)->val);
	ft_free(*lst);
	*lst = tmp;
}

void	clean_lst_env(t_env_lst **lst)
{
	while ((*lst))
		clean_node_env(lst);
}

void	copy_list(t_env_lst *env, t_env_lst **new)
{
	t_env_lst	*tmp;
	t_env_lst	*node;
	t_env_lst	*last;

	*new = NULL;
	tmp = env;
	while (tmp)
	{
		node = ft_malloc(sizeof(t_env_lst));
		node->name = ft_strdup(tmp->name);
		node->val = ft_strdup(tmp->val);
		node->next = NULL;
		if (!*new)
			*new = node;
		else
		{
			last = *new;
			while (last->next)
				last = last->next;
			last->next = node;
		}
		tmp = tmp->next;
	}
}
