/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:34:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/16 01:47:39 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	spec_symb(char *s, int i)
{
	if (s[i] == '|' || s[i] == '\'' || s[i] == '\"')
		return (1);
	else if (s[i] == '<')
	{
		if (s[i + 1] && (s[i + 1] == '<'))
			return (2);
		return (1);
	}
	else if (s[i] == '>')
	{
		if (s[i + 1] && (s[i + 1] == '>'))
			return (2);
		return (1);
	}
	return (0);
}

int	pass_str(char *s, char q)
{
	int	i;

	i = 0;
	if (q)
	{
		while (s[i] && s[i] != q)
			i++;
	}
	else
	{
		while ((s[i] && !spec_symb(s, i)) && !space(s[i]))
			i++;
	}
	return (--i);
}
//*redo token search to handle cases:
//echo"hello" vs echo "hello" //WORD vs WORD QUOTED_STR
//ec"ho" "hello" //WORD QUOTED_STR
//ec"ho""hello" //WORD
void	init_token_arr(char *s, t_mshell *mshell)
{
	int		len;
	char	q;
	int		i;

	len = 0;
	q = '\0';
	i = -1;
	while (s[++i])
	{
		printf("%s%d %c%s	", YELLOW, i, s[i], RE);
		quote_opened_type(s[i], &q);
		// if (space(s[i]) && !q)
		// 	continue ;
		// 
		if (((spec_symb(s, i) || space(s[i])) && !q) || s[i] == q)
		{
			if (spec_symb(s, i) == 2)
				i++;
			len++;
		}
		else
		{
			i += pass_str(&s[i], q);
			len++;
		}
		printf("%s%d %c%s\n", GREEN, i, s[i], RE);
	}
	mshell->s_token_arr = malloc(sizeof(t_token) * len);
	printf("len:%d\n", len);
}
