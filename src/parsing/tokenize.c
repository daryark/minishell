/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:34:22 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/19 00:55:42 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	pass_quoted_str(char *s, char *q)
{
	int i;

	i = 0;
	printf("%s%c%s", RED, s[i], RE);
	i++;
	while (s[i] && s[i] != *q)
	{
		printf("%s%c%s", RED, s[i], RE);
		i++;
	}
	quote_opened_type(s[i], q);
	return (i);
}

int	pass_str(char *s, char *q)
{
	int	i;

	i = 0;
	if (*q)
		i+= pass_quoted_str(s, q);
	else
	{
		while ((s[i] && !spec_symb(s, i)) && !space(s[i]))
		{
			quote_opened_type(s[i], q);
			if (*q)
				i += pass_quoted_str(&s[i], q);
			printf("%s%c%s", RED, s[i], RE);
			i++;
		}
		i--;
	}
	return (i);
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
		if (space(s[i]) && !q)
			continue ;
		if (spec_symb(s, i) && !q)
		{
			if (spec_symb(s, i) == 2)
				i++;
		}
		else
			i += pass_str(&s[i], &q);
		len++;
		printf("%s%d %c%s\n", GREEN, i, s[i], RE);
	}
	mshell->s_token_arr = malloc(sizeof(t_token) * len);
	printf("len:%d\n", len);
}

// void    add_quote_token(char c)
// {
//     if (*s == '\'')
//         add_token(c, 1, )
// }

// void    prep_token(char *s, int len)
// {
//     if (len == 1)
//     {
//         if (*s == '|')
//             add_token()
//     }
// }