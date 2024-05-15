/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:30:36 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/15 17:53:51 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_mshell	t_mshell;

//err check
void			syntax_err(int c);
int				input_err_check(char *input);
//parsing
void			init_env(t_mshell *mshell, char **env);
int				parse_input(char *input, t_mshell *mshell);

void			dollar_question_replace(char **s, int i, t_mshell *mshell);
//parsing utils
int				space(char c);
int             quote(char c);
int				arr_len(char **arr);
int				ft_strchr_pos(char *s, int c);
void			quote_opened_type(char c, char *q);

#endif