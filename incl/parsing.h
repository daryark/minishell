/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:30:36 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/19 17:13:20 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum 			e_type
{
	T_WORD = 0,	//word, string, file ...
	T_DQUOTE,	//"
	T_SQUOTE,	//'
	T_PIPE,		//|
	T_LREDIR,	//<
	T_RREDIR,	//>
	T_HEREDOC,	//<<
	T_ADDREDIR,	//>>
	T_CMD,		//command
	T_SP,		//space
	T_NL,		//newline
}						t_type;

typedef struct 			s_token
{
	char				*word;
	t_type				type; //or char ? '|', '\"', 'w'-for word; 'c' - for cmd...?
}						t_token;

typedef struct 			s_env_lst
{
	char				*val;
	char				*name;
	struct s_env_lst	*next;
}						t_env_lst;

typedef struct 			s_mshell
{
	t_env_lst			*env;
	char				**envp;
	t_token				*s_token_arr;
	char				*input;
	int					exit_status;

}						t_mshell;

//err check
void			syntax_err(int c);
int				input_err_check(char *input);
//parsing
void			init_env(t_mshell *mshell, char **env);
int				fill_str(char *s, t_env_lst **lst);
int				parse_input(char *input, t_mshell *mshell);
// void			replace_dollars(char **s, t_mshell *mshell);
void			dollar_value_subst(char **s, char *q, t_mshell *mshell);
// void			dollar_replace(char **s, int st, int en, t_mshell *mshell);
//parsing utils
int				space(char c);
int             quote(char c);
int				spec_symb(char *s, int i);
void			quote_opened_type(char c, char *q);
int				arr_len(char **arr); //!delete definition and fn
int				env_lst_len(t_env_lst *lst);//*this fn instead
int				ft_strchr_pos(char *s, int c);
t_env_lst		*find_evn_var(char *name, t_env_lst *env);
void            init_token_arr(char *s, t_mshell *mshell);

#endif