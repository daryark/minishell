/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:24 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/13 18:48:38 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i] != NULL)
	{
		j = i + 1;
		while (envp[j] != NULL)
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**ft_add_var(char **envp, char *var)
{
	int		i;
	int		found;
	char	**new_envp;

	found = 0;
	i = 0;
	while (envp[i] != NULL)
		i++;
	new_envp = ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			found = 1;
		i++;
	}
	if (found == 1)
		printf("export: '%s': not a valid identifier\n", var);
	else
		new_envp[i] = ft_strdup(var);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

void	ft_export(t_mshell *mshell)
{
	int		i;
	char	**new_vars;

	if (ft_strlen(mshell->input) == 6)
	{
		sort_env(mshell->envp);
		i = 0;
		while (mshell->envp[i] != NULL)
		{
			printf("declare -x %s\n", mshell->envp[i]);
			i++;
		}
	}
	else
	{
		new_vars = ft_split(mshell->input, ' ');
		i = 1;
		while (new_vars[i] != NULL)
		{
			mshell->envp = ft_add_var(mshell->envp, new_vars[i]);
			i++;
		}
	}
}

char	**ft_remove_var(char **envp, char *var)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	new_envp = ft_malloc(sizeof(char *) * (arr_len(envp) + 1));
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) != 0)
		{
			new_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	if (j == arr_len(envp))
		printf("unset: '%s': not a valid identifier\n", var);
	else
		new_envp[j] = NULL;
	return (new_envp);
}

void	ft_unset(t_mshell *mshell)
{
	int		i;
	char	**rm_vars;

	i = 0;
	if (ft_strlen(mshell->input) == 5)
		printf("unset: not enough arguments\n");
	else
	{
		rm_vars = ft_split(mshell->input, ' ');
		i = 1;
		while (rm_vars[i] != NULL)
		{
			mshell->envp = ft_remove_var(mshell->envp, rm_vars[i]);
			i++;
		}
	}
}
