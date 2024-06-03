/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:05:31 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/03 16:16:49 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_cmds(t_mshell *mshell)
{
	int	c;
	int	i;

	c = -1;
	printf("%s---------PRINT CMDS------------%s", GREEN, RE);
	printf("len cmds:%d\n\n", mshell->cmdarr_l);
	while (++c < mshell->cmdarr_l)
	{
		printf("cmd N: %d\nargs: ", c);
		i = -1;
		while (mshell->cmdarr[c].args[++i] != NULL)
			printf("(%s), ", mshell->cmdarr[c].args[i]);
		i = -1;
		printf("\ninp: ");
		while (++i < mshell->cmdarr[c].inp_l)
			printf("{t: %i, w: %s},", mshell->cmdarr[c].inp[i].type, \
				mshell->cmdarr[c].inp[i].word);
		i = -1;
		printf("\nout: ");
		while (++i < mshell->cmdarr[c].out_l)
			printf("{t: %i, w: %s},", mshell->cmdarr[c].out[i].type, \
				mshell->cmdarr[c].out[i].word);
		printf("\n%s-------------------------%s\n", GREEN, RE);
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
