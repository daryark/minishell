/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:43:20 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/31 14:54:32 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*trim_input(char *src)
{
	int		i;
	int		d;
	char	q;
	char	*dst;

	i = -1;
	d = 0;
	q = '\0';
	if (!src)
		return (NULL);	
	while (src[++i])
	{
		quote_opened_type(src[i], &q);
		if (!(((space(src[i]) && space(src[i + 1])) || (space(src[i]) && (!d
							|| !src[i + 1]))) && !q))
			d++;
	}
	dst = (char *)ft_calloc(sizeof(char), d + 1);
	if (!dst)
		alloc_err();
	i = -1;
	d = 0;
	while (src[++i])
	{
		quote_opened_type(src[i], &q);
		if (!(((space(src[i]) && space(src[i + 1])) || (space(src[i]) && (!d
							|| !src[i + 1]))) && !q))
			dst[d++] = src[i];
	}
	return (dst);
}

static void	replace_dollars(char **s, t_mshell *mshell)
{
	char	**dllr_arr;
	int		i;
	char	q;

	dllr_arr = split_save_divider(*s, '$');
	q = '\0';
	i = -1;
	while (dllr_arr[++i])
		dollar_value_subst(&dllr_arr[i], &q, mshell);
	ft_free(*s);
	*s = arrjoin(dllr_arr);
	ft_free_array(dllr_arr);
}

// word - text or pipe/redir symb, type - number of type
static void	split_tokens(char *s, t_mshell *mshell)
{
	int	i;
	int	a_i;
	int	w_l;

	i = -1;
	a_i = 0;
	init_tokarr(s, mshell);
	while (s[++i])
	{
		if (space(s[i]))
			continue ;
		mshell->tokarr[a_i].type = token_typizator(&s[i]);
		w_l = spec_symb(&s[i]);
		if (!w_l)
			w_l = pass_str(&s[i]);
		mshell->tokarr[a_i].word = ft_substr(s, i, w_l--);
		i += w_l;
		// printf("%s%s%s	", GREEN, mshell->tokarr[a_i].word, RE);
		// printf("%s%d%s\n", YELLOW, mshell->tokarr[a_i].type, RE);
		a_i++;
	}
	// printf("tokarr_l:%d\n", mshell->tokarr_l);
}

// cmdarr [{args - arr[char *],
// inp - arr[word - file, type - type red_inp/heredoc],
// out - arr[word - file, type - type red_out/append]}, {args, inp, out}];
static void	create_cmdarr(t_mshell *mshell)
{
	int	c;
	int	t;

	init_cmdarr(mshell);
	c = -1;
	t = 0;
	while (++c < mshell->cmdarr_l)
	{
		fill_cmd(c, &t, mshell);
		t++;
	}
	// print_cmds(mshell);
}

int	parse_input(char *input, t_mshell *mshell)
{
	char	*dst;
	char	err;

	if (input_err_check(input) || empty_str(input))
		return (0);
	dst = trim_input(input);
	// printf("%s trim:	|%s|\n%s", GREEN, dst, RE);
	replace_dollars(&dst, mshell);
	// printf("%s $:	|%s|\n%s", GREEN, dst, RE);
	split_tokens(dst, mshell);
	err = token_order_check(mshell);
	if (err >= 0 && !leave_heredoc(mshell, err))
		return (ft_free(dst), 0);
	open_quotes(mshell);
	if (err < 0)
		create_cmdarr(mshell);
	ft_free(dst);
	printf("%sPARSED%s\n", GREEN, RE);
	return (1);
}
