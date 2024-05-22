/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:30:36 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/05/20 14:34:39 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_type
{
	T_WORD = 0, // word, string, file ...
	T_DQUOTE,   //"
	T_SQUOTE,   //'
	T_PIPE,     //|
	T_LREDIR,   //<
	T_RREDIR,   //>
	T_HEREDOC,  //<<
	T_ADDREDIR, //>>
	T_CMD,      // command
	T_SP,       // space
	T_NL,       // newline
}						t_type;

typedef struct s_token
{
	char				*word;
	t_type type; // or char ? '|', '\"', 'w'-for word; 'c' - for cmd...?
}						t_token;

typedef struct s_env_lst
{
	char				*val;
	char				*name;
	struct s_env_lst	*next;
}						t_env_lst;

typedef struct s_mshell
{
	t_env_lst			*env;
	char				**envp;
	t_token				*s_token_arr;
	char				*input;
	int					exit_status;

}						t_mshell;

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
int						spec_symb(char *s, int i);
void					quote_opened_type(char c, char *q);
int						env_lst_len(t_env_lst *lst);
int						ft_strchr_pos(char *s, int c);
void					init_token_arr(char *s, t_mshell *mshell);

#endif