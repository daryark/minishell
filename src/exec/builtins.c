/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/13 18:56:15 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	ft_execute(t_mshell *mshell)
{
	if (ft_strncmp(mshell->input, "cd", 2) == 0)
		ft_cd(mshell->input);
	else if (ft_strncmp(mshell->input, "echo", 4) == 0)
		ft_echo(mshell);
	else if (ft_strncmp(mshell->input, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(mshell->input, "env", 3) == 0)
		ft_env(mshell);
	else if (ft_strncmp(mshell->input, "export", 6) == 0)
		ft_export(mshell);
	else if (ft_strncmp(mshell->input, "unset", 5) == 0)
		ft_unset(mshell);
	else
		ft_exec_just_cmd(mshell);
}

void	ft_cd(char *cmd)
{
	char	**tmp;
	char	*path;

	tmp = ft_split(cmd, ' ');
	if (tmp[1] == NULL)
	{
		path = ft_strdup("/home");
		chdir(path);
		ft_free(path);
	}
	else
	{
		chdir(tmp[1]);
		ft_free(tmp[1]);
	}
	ft_free(tmp);
}

void	ft_env(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->envp[i] != NULL)
	{
		printf("%s\n", mshell->envp[i]);
		i++;
	}
}

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	ft_free(path);
}
