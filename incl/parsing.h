/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:30:36 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/24 14:31:56 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_mshell		t_mshell;
typedef struct s_builtin	t_builtin;

typedef enum e_type
{
	T_WORD = 1,	// word, string, file, command ...
	T_PIPE,		//|
	T_HEREDOC,	//<<
	T_RED_FROM,	//<
	T_APPEND,	//>>
	T_RED_TO,	//>
	T_NL,		// *newline ??
}						t_type;

typedef struct s_token
{
	char				*word;
	t_type				type;
}						t_token;

// typedef struct s_cmdarr
// {
// 	char	*cmd;
// 	char	*args; //(files and strings..) ? if i need it or put with cmd?
// 	char	**options; //arr[str] -flags
// 	t_type	*in; //arr[struct{name, type}];
// 	t_type	*out; //arr[struct{name, type}];

// };


typedef struct s_env_lst
{
	char				*val;
	char				*name;
	struct s_env_lst	*next;
}						t_env_lst;

// err check
void					syntax_err(int c);
int						input_err_check(char *input);
// parsing
void					init_env(t_mshell *mshell, char **env);
int						fill_str(char *s, t_env_lst **lst);
int						parse_input(char *input, t_mshell *mshell);
// void			replace_dollars(char **s, t_mshell *mshell);
void					dollar_value_subst(char **s, char *q, t_mshell *mshell);
// void			dollar_replace(char **s, int st, int en, t_mshell *mshell);
// parsing utils
int						space(char c);
int						quote(char c);
int						spec_symb(char *s);
void					quote_opened_type(char c, char *q);
int						pass_str(char *s);
int						env_lst_len(t_env_lst *lst);
int						ft_strchr_pos(char *s, int c);
char					*cut_name(char *s);
t_env_lst				*find_env_node(char *name, t_env_lst *env);
void					init_token_arr(char *s, t_mshell *mshell);
t_type					token_typizator(char *s);

#endif