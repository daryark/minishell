/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:30:07 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/19 17:15:21 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


t_env_lst	*find_evn_var(char *name, t_env_lst *env)
{
	while (env->next)
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
	char		*value;
	char		*name;
	t_env_lst	*target;

	value = NULL;
	name = NULL;
	target = NULL;
	while (s[*i] && (ft_isalnum(s[*i] || s[*i] == '_')))
		(*i)++;
	name = ft_substr(s, 1, (*i) - 1);
	if (!name)
		return (NULL);
	target = find_evn_var(name, env);
	if (target != NULL)
		value = ft_strdup(target->val);
	if (!value)
		value = ft_calloc(sizeof(char), 1);
	return (ft_free(name), value);
}

//question sign $? or $?blahd
//return i from which copy str
static int	question_case(char *s)
{
	if (s[2])
		return (2);
	else
		return (ft_strlen(s));
}

//return -1 if not a case, 0/1 if yes,
//0/1 - i form which copy str (leave or not $ at start)
static int	not_replace_cases(char *s, char q)
{
	if (s[0] != '$')
		return (0);
	else if (space(s[1]) || !s[1] || q == '\''
		|| (q && (spec_symb(s, 1) || quote(s[1]))))
		return (0);
	else if (!q && (spec_symb(s, 1) || quote(s[1])))
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
//String with one dollar (from splited arr) passed in arg
void	dollar_value_subst(char **s, char *q, t_mshell *mshell)
{
	int		i;
	char	*new;

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
