/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:31:17 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/03 12:01:38 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_env(t_mshell *mshell)
{
	t_env_lst	*tmp;

	tmp = mshell->env;
	if (!mshell->export)
	{
		while (tmp)
		{
			if (tmp->val)
				printf("%s=%s\n", tmp->name, tmp->val);
			tmp = tmp->next;
		}
		mshell->exit_status = 0;
		return ;
	}
	tmp = mshell->export;
	while (tmp)
	{
		if (tmp->val)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->val);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	mshell->exit_status = 0;
}

void	ft_export(t_mshell *mshell)
{
	char	**args;

	args = mshell->cmdarr[mshell->cmd_num].args;
	if (args[1] == NULL)
	{
		copy_list(mshell->env, &mshell->export);
		remove_one_node("_", &mshell->export);
		tmp_sort_env(mshell->export);
		ft_env(mshell);
		clean_lst_env(&mshell->export);
	}
	else
		export_loop(mshell, args, 1);
	mshell->exit_status = 0;
}

void	ft_unset(t_mshell *mshell)
{
	int		i;
	char	**rm_names;

	rm_names = mshell->cmdarr[mshell->cmd_num].args;
	if (rm_names[1] == NULL)
	{
		printf("minishell: unset: not enough arguments\n");
		mshell->exit_status = 1;
		return ;
	}
	else
	{
		i = 1;
		while (rm_names[i] != NULL)
		{
			remove_one_node(rm_names[i], &mshell->env);
			i++;
		}
	}
	mshell->exit_status = 0;
}

int	ft_exit(t_mshell *mshell, char *input)
{
	if (ft_strcmp("exit", mshell->cmdarr[0].args[0]) == 0)
	{
		ft_free(input);
		printf("exit\n");
		if (!mshell->cmdarr[0].args[1])
			exit(mshell->exit_status);
		else if (mshell->cmdarr[0].args[1]
			&& !ft_isdigit(mshell->cmdarr[0].args[1][0]))
			ft_error_exit("exit: ", "numeric argument required", 2);
		else if (ft_isdigit(mshell->cmdarr[0].args[1][0])
			&& mshell->cmdarr[0].args[2])
		{
			ft_error_return("exit: ", "too many arguments", mshell, 1);
			return (1);
		}
		else if (mshell->cmdarr[0].args[1])
			exit(ft_atoi(mshell->cmdarr[0].args[1]));
	}
	return (0);
}
