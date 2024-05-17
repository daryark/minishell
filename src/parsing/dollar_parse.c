/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:30:07 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/17 23:24:19 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*find_env_var(char *name, t_env_lst *env)
{
	char	*value;

	value = NULL;
	while (env->next)
	{
		if (ft_strlen(name) == ft_strlen(env->name)
			&& !ft_strncmp(name, env->name, ft_strlen(name)))
		{
			value = ft_strdup(env->val);
			break ;
		}
		env = env->next;
	}
	if (!value)
		value = ft_calloc(sizeof(char), 1);
	return (value);
}

//cases: nothing changes || "" str instead of $...
//exit if alloc failed. return 0 -> if not a case, 1 - if it is, and worked
// static int	spec_cases(char **s, char q)
// {
// 	if (((*s)[0] == '$' && (((*s)[1] == space((*s)[1]) || !(*s)[1])
// 				|| (q && ((*s)[1] == spec_symb(*s, 1) || quote((*s)[1])))
// 				|| (q == '\''))) || (*s)[0] != '$')
// 		return (1);
// 	else if (!q && ((*s)[1] == spec_symb(*s, 1) || quote((*s)[1])))
// 	{
// 		printf("second if\n");
// 		ft_free(*s);
// 		*s = ft_calloc(sizeof(char), 1);
// 		if (!s)
// 			alloc_err();
// 		return (1);
// 	}
// 	printf("not spec_case\n");
// 	return (0);
// }

//  //question sign $? or $?blahd
// static int	question_case(char **s, char q, t_mshell *mshell)
// {
// 	char *new;
// 	if ((*s)[1] == '?' && (*s)[2])
// 	{
// 		printf("third if\n");
// 		new = ft_strjoin(ft_itoa(mshell->exit_status), &(*s)[2]);
// 	}
// 	else if ((*s)[1] == '?' && !(*s)[2])
// 	{
// 		printf("fourth if\n");
// 		new = ft_itoa(mshell->exit_status);
// 	}
// }

//*   echo$ "$"  echo$ "$" '$' "$<" $< adfds $df
//String with one dollar (from splited arr) passed in arg
void	dollar_value_subst(char **s, char *q, t_mshell *mshell)
{
	char	*new;
	int		i;
	char	*name;

	name = NULL;
	//spec cases
	printf("%ss:%s,	q:%c%s	", YELLOW, *s, *q, RE);
	if ((*s)[0] != '$')
	{
		printf("first if no dollar\n");
		new = ft_strdup(*s);
		if (!new)
			alloc_err();
	}
	else if (space((*s)[1]))
	{
		printf("first if, space after\n");
		new = ft_strdup(*s);
		if (!new)
			alloc_err();
	}
	else if (!(*s)[1])
	{
		printf("first if, dollar only\n");
		new = ft_strdup(*s);
		if (!new)
			alloc_err();
	}
	else if (*q == '\'')
	{
		printf("first if, in single quote\n");
		new = ft_strdup(*s);
		if (!new)
			alloc_err();
	}
	else if (*q && (spec_symb(*s, 1) || quote((*s)[1])))
	{
		printf("first if, in quote+spec_symb|quote after\n");
		new = ft_strdup(*s);
		if (!new)
			alloc_err();
	}
	else if (!*q && (spec_symb(*s, 1) || quote((*s)[1])))
	{
		printf("second if\n");
		new = ft_strdup(&(*s)[1]);
		if (!new)
			alloc_err();
	}
	else if ((*s)[1] == '?' && (*s)[2]) //question sign
	{
		printf("third if\n");
		new = ft_strjoin(ft_itoa(mshell->exit_status), &(*s)[2]);
		if (!new)
			alloc_err();
	}
	else if ((*s)[1] == '?' && !(*s)[2])
	{
		printf("fourth if\n");
		new = ft_itoa(mshell->exit_status);
		if (!new)
			alloc_err();
	}
	else //other type of input (alphanumeric characters) in "" or without any
	{
		new = ft_strdup(*s);
		if (!new)
			alloc_err();
		printf("fifth if. ELSE\n");
		i = 1;
		while ((*s)[i] && ft_isalnum((*s)[i]))
			i++;
		name = ft_substr(*s, 1, --i);
		if (!name)
			alloc_err();
		new = find_env_var(name, mshell->env);
		if (!new)
			alloc_err();
		ft_free(name);
	}
	i = -1;
	while ((*s)[++i])
		quote_opened_type((*s)[i], q);
	ft_free(*s);
	*s = new;
}
