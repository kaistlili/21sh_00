/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

#include "sh_core.h"


#define DQUOTE_ERR 10
#define SQUOTE_ERR 11
#define BAD_SUB	12
#define INCOMPLETE_SUB 13
#define ENDOFINPUT 14 


#define INPUTSZ 1024

typedef	struct	s_str
{
	char	*str;
	size_t	size;
	size_t	len;
}				t_str;

typedef	enum	e_token_type
{
	WORD,
	NEWLINE,
	IO_NUM,
	FILENAME,
	ASSIGN,
	PIPE,
	SEMI_COL,
	AMPERS,
	AND_IF,
	OR_IF,
	LESSAND,
	GREATAND,
	DGREAT,
	LESS,
	GREAT,
}				t_token_type;

typedef	struct	s_token
{
	t_token_type	type;
	t_str			data;
	struct s_token	*next;	
}				t_token;

typedef struct	s_parser
{
	struct s_token		*current;
	struct s_token 		*head;
	
	struct s_simple_cmd	*cmd;
	struct s_redir		*current_redir;	
	
	struct	s_simple_cmd *pipeline;
//	t_ast	**head;
}				t_parser;

/*
Lexer jump table
*/
typedef int (*t_func)(char**, t_token*);

int handle_dquote(char **input, t_token *token);
int handle_digit(char **input, t_token *token);
int handle_common(char **input, t_token *token);
int handle_ampersand(char **input, t_token *token);
int handle_squote(char **input, t_token *token);
int handle_semic(char **input, t_token *token);
int handle_less(char **input, t_token *token);
int handle_great(char **input, t_token *token);
int handle_column(char **input, t_token *token);

int	test_sh_parser(t_token *start);
/*
	intermediate cmd functions
*/
typedef struct s_redir t_redir;
typedef struct s_simple_cmd t_simple_cmd;
// test functions
void	print_token(t_token *t);
void	print_tokens(t_token *start);
void	test_simplecmd(t_simple_cmd *cmd);
void	test_pipeline(t_parser *parser);
//
int	add_to_pipeline(t_parser *parser);
int	build_redir(t_token *to_add, t_redir *redir);
int	build_cmd(t_token *to_add, t_simple_cmd *cmd);
void	add_redir_lst(t_redir *to_add, t_redir **head);
/*
recursive decent functions 
*/
int	expect_linebreak(t_parser *parser);
int	expect_separator_op(t_parser *parser);
int	expect_separator(t_parser *parser);
int	expect_filename(t_parser *parser);
int	expect_io_file(t_parser *parser);
int	expect_io_redir(t_parser *parser);
int	expect_assign(t_parser *parser);
int	expect_cmd_pre(t_parser *parser);
int	expect_word(t_parser *parser);
int	expect_cmd_suffix(t_parser *parser);
int	expect_cmd_name(t_parser *parser);
int	expect_simeple_cmd(t_parser *parser);
int	expect_pipeline_suffix(t_parser *parser);
int	expect_pipeline(t_parser *parser);
int	expect_and_or_suffix(t_parser *parser);
int	expect_and_or(t_parser *parser);
int	expect_list_suffix(t_parser *parser);
int	expect_list(t_parser *parser);
int	expect_complete_cmd(t_parser *parser);

/*parser util functions */
int	parser_is_assign(t_token const *token);
int	parser_is_name_c(char c);
int next_squote(char *str, int index);
int	next_dquote(char *str, int index);
int	next_bslash(char *str, int index);
/*t_str functions*/
int	str_putnstr(char *str, t_str *data, size_t n);
int	str_putchar(char **c, t_str *data);
int	ft_str_realloc(t_str *str_st, size_t newsz);


/*random util functions*/
int	ft_is_ifs(char c);

void	add_token(t_token **head, t_token *to_add);
t_token	*dup_token(t_token *token);
t_token	*new_token(int type);
void	free_token(t_token *token);
void	free_token_lst(t_token *token);
t_token	*ft_tokenizer(char *line);
//int	next_token(char **line, t_token *token);
int	next_token(char *line, t_token **head);
#endif
