/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft.h"

#define DQUOTE_ERR 10
#define INPUTSZ 1024
#define MEMERR 1
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
/*
typedef enum	e_non_term
{
	complete_cmd,
	list,
	and_or,
	pipeline,
	simple_cmd,
	cmd_word,
	cmd_pre,
	cmd_suf,
	io_redir,
	io_file,
	filename,
	separator,
	separator_op,
	line_break,
	new_line_lst
}				t_non_term;

typeef	union	u_type
{
	enum e_non_term	terminal;
	enum e_non_term non_terminal;	
}				t_type;
*/
typedef	struct	s_token
{
	t_token_type	type;
	t_str			data;
	struct s_token	*next;	
}				t_token;

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

int	str_putchar(char c, t_str *data);
int	ft_str_realloc(t_str *str_st, size_t newsz);
int	ft_is_ifs(char c);
