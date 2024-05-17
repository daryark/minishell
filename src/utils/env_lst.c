/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 01:00:02 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/17 20:21:27 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_lstadd_env(t_env_lst **lst, char *name, char *val)
{
	t_env_lst	*node;
	t_env_lst	*head;

	node = malloc(sizeof(t_env_lst));
	if (!node)
		alloc_err();
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
