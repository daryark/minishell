/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:30:07 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/30 13:43:16 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//cut env name from str
char	*cut_name(char *s)
{
	int		i;
	char	*name;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	name = ft_substr(s, 0, i);
	if (!name)
		alloc_err();
	return (name);
}

//takes the name str and returns node with name:val, or NULL
t_env_lst	*find_env_node(char *name, t_env_lst *env)
{
	while (env)
	{
		if (ft_strlen(name) == ft_strlen(env->name)
			&& !ft_strncmp(name, env->name, ft_strlen(name)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

//finds part with env_var name in *s, updates *i(to pass back in strjoin)
//return env_var value
static char	*find_replace_env_var(char *s, int *i, t_env_lst *env)
{
	char		*find;
	t_env_lst	*target;

	find = cut_name(&s[*i]);
	target = find_env_node(find, env);
	*i += ft_strlen(find);
	ft_free(find);
	if (!target || !target->val)
		find = ft_calloc(sizeof(char), 1);
	else
		find = ft_strdup(target->val);
	return (find);
}

// question sign $? or $?blahd
// return i from which copy str
static int	question_case(char *s)
{
	if (s[2])
		return (2);
	else
		return (ft_strlen(s));
}

// return -1/-2 no, 0/1 - yes
//-1 - standard ($ at start), -2 (no $ at start, still can be in the mid)
// 0/1 -yes, i to copy str from (leave or not $ at start)
static int	not_replace_cases(char *s, char q)
{
	if (s[0] != '$' && q != '\"')
		return (0);
	else if (q == '\"' && s[1] != '$')
	{
		return (-2);
	printf("in the middle dollar can be\n");
	}
	else if (space(s[1]) || !s[1] || q == '\''
		|| (q && (spec_symb(&s[1]) || quote(s[1]))))
		return (0);
	else if (!q && (spec_symb(&s[1]) || quote(s[1])))
		return (1);
	return (-1);
}

static char	*replace_cases(char *s, t_mshell *mshell)
{
	char	*subst;
	int		i;

	subst = NULL;
	if (s[1] == '?')
	{
		i = question_case(s);
		subst = ft_itoa(mshell->exit_status);
	}
	else
	{
		i = 1;
		subst = find_replace_env_var(s, &i, mshell->env);
	}
	return (ft_strjoin(subst, &s[i]));
}

//*   echo$ "$"  echo$ "$" '$' "$<" $< adfds $df $PATH
// String with one dollar (from splited arr) passed in arg
void	dollar_value_subst(char **s, char *q, t_mshell *mshell)
{
	int		i;
	char	*new;

	// printf("%s%s%s\n", YELLOW, *s, RE);
	i = not_replace_cases(*s, *q);
	if (i >= 0)
		new = ft_strdup(&(*s)[i]);
	else
		new = replace_cases(*s, mshell);
	if (!new)
		alloc_err();
	i = -1;
	while ((*s)[++i])
		quote_opened_type((*s)[i], q);
	ft_free(*s);
	*s = new;
}
