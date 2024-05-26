/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:22:23 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/26 17:14:16 by dyarkovs         ###   ########.fr       */
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

	c = 0;
	printf("%s---------PRINT CMDS------------%s", GREEN, RE);
	printf("len cmds:%d\n\n", mshell->cmdarr_l);
	while (c < mshell->cmdarr_l)
	{
		printf("cmd N: %d\nargs: ", c);
		i = 0;
		while (mshell->cmdarr[c].args[i] != NULL)
		{
			printf("%s ", mshell->cmdarr[c].args[i]);
			i++;
		}
		i = 0;
		printf("\ninp: ");
		while (i < mshell->cmdarr[c].inp_l)
		{
			printf("{t: %i, w: %s},", \
			mshell->cmdarr[c].inp[i].type, mshell->cmdarr[c].inp[i].word);
			i++;
		}
		i = 0;
		printf("\nout: ");
		while (i < mshell->cmdarr[c].out_l)
		{
			printf("{t: %i, w: %s},", \
			mshell->cmdarr[c].out[i].type, mshell->cmdarr[c].out[i].word);
			i++;
		}
		printf("\n%s-------------------------%s\n", GREEN, RE);
		c++;
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
