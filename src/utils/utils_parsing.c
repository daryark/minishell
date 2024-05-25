/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:22:23 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/26 00:26:59 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// finds position from start of s.
// Not iteration(from 0), iterates from 1!
int	ft_strchr_pos(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (unsigned char)c && s[i])
		i++;
	if (s[i] == (unsigned char)c)
		return (++i);
	return (-1);
}

void	print_cmds(t_mshell *mshell)
{
	int	c;
	int	i;

	c = -1;
	while (++c < mshell->cmdarr_len)
	{
		printf("cmd N: %d\nargs: ", c);
		printf("---");
		i = -1;
		while (mshell->cmdarr[c].args[++i] != NULL)
			printf("%s ", mshell->cmdarr[c].args[i]);
		i = -1;
		printf("\ninp: ");
		while (mshell->cmdarr[c].inp[++i].word != NULL)
			printf("{t: %i, w: %s},", \
			mshell->cmdarr[c].inp[i].type, mshell->cmdarr[c].inp[i].word);
		i = -1;
		printf("\nout: ");
		while (mshell->cmdarr[c].out[++i].word != NULL)
			printf("{t: %i, w: %s},", \
			mshell->cmdarr[c].out[i].type, mshell->cmdarr[c].out[i].word);
		printf("\n\n");
	}
}

void	print_env(t_env_lst *env)
{
	while (env)
	{
		printf("%s%s = %s%s%s\n", YELLOW, env->name, GREEN, env->val, RE);
		env = env->next;
	}
}
