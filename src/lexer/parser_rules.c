/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_lexer.h"
/*ft_printf("function: %s\n", "");
ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
*/
int	next_sym(t_parser *parser)
{
	if (!(parser->current->next))
		next_token(NULL, &(parser->current));	
	parser->current = parser->current->next; /* to add malloc fail checks */
	return (0);
}

int	expect_linebreak(t_parser *parser)
{
	(void)parser;
	return (1);	
}

int	expect_separator_op(t_parser *parser)
{
	ft_printf("function: %s\n", "sep_op");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if ((parser->current->type == AMPERS)
		|| (parser->current->type == SEMI_COL))
	{
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_separator(t_parser *parser)
{
	ft_printf("function: %s\n", "sep");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if (expect_separator_op(parser))
		return (1);
	return (0);

}


int	expect_filename(t_parser *parser)
{
/* expand stuff here, see posix rule 2
*/
	ft_printf("function: %s\n", "filename");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if (parser->current->type == WORD)
	{
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_io_file(t_parser *parser)
{
	t_token *backtrack;

	ft_printf("function: %s\n", "io_file");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	backtrack = parser->current;
	if ((parser->current->type >= LESSAND)
		&& (parser->current->type <= GREAT))
	{
		parser->current = parser->current->next;
		if (expect_filename(parser))
			return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	expect_io_redir(t_parser *parser)
{
	t_token *backtrack;

	ft_printf("function: %s\n", "io_redir");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	backtrack = parser->current;
	if (parser->current->type == IO_NUM)
	{
		parser->current = parser->current->next;
		if (expect_io_file(parser))
			return (1);
	}
	else if (expect_io_file(parser))
		return (1);
	parser->current = backtrack;
	return (0);

}

int	expect_assign(t_parser *parser)
{
	ft_printf("function: %s\n", "assign");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if (parser_is_assign(parser->current))
	{
		parser->current->type = ASSIGN;
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_cmd_pre(t_parser *parser)
{
	ft_printf("function: %s\n", "cmd_pre");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if ((expect_io_redir(parser))
		|| (expect_assign(parser)))
	{
		expect_cmd_pre(parser);
		return (1);
	}
	return (0);
}

int	expect_word(t_parser *parser)
{
	ft_printf("function: %s\n", "word");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if (parser->current->type == WORD)
	{
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_cmd_suffix(t_parser *parser)
{
	ft_printf("function: %s\n", "cmd_suffix");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if ((expect_io_redir(parser))
		|| (expect_word(parser)))
	{
		expect_cmd_suffix(parser);
		return (1);
	}
	return (0);
		
}

int	expect_cmd_name(t_parser *parser)
{
	ft_printf("function: %s\n", "cmd_name");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if ((parser->current->type == WORD)
			&& (!parser_is_assign(parser->current)))
	{   
		//we never get here is current tok is assign so check is redundant ?
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_simple_cmd(t_parser *parser)
{
	ft_printf("function: %s\n", "simple_cmd");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	//here we start building cmd struct
	t_token *backtrack;
	
	backtrack = parser->current;
	if (expect_cmd_pre(parser))
	{
		//if (expect_cmd_word(parser))
		if (expect_cmd_name(parser))
			expect_cmd_suffix(parser);
		return (1);
	}
	else if (expect_cmd_name(parser))
	{
		expect_cmd_suffix(parser);
		return (1);
	}
	parser->current = backtrack;	
	return (0);
}

int	expect_pipeline_suffix(t_parser *parser)
{
	ft_printf("function: %s\n", "pipline_suffix");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	t_token *backtrack;

	backtrack = parser->current;
	if (parser->current->type == PIPE)
	{
		parser->current = parser->current->next;
		expect_linebreak(parser);
		if (!expect_simple_cmd(parser))
		{
			parser->current = backtrack;	
			return (0);
		}
	}
	return (1);
}

int	expect_pipeline(t_parser *parser)
{
	ft_printf("function: %s\n", "pipeline");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	t_token *backtrack;

	backtrack = parser->current;
	if (expect_simple_cmd(parser))
	{
		if (expect_pipeline_suffix(parser))
			return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	expect_and_or_suffix(t_parser *parser)
{
	ft_printf("function: %s\n", "and_or_suffix");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	t_token *backtrack;

	backtrack = parser->current;
	if ((parser->current->type == AND_IF)
		|| (parser->current->type == OR_IF))
	{
		parser->current = parser->current->next;
		expect_linebreak(parser);
		if (!expect_pipeline(parser))
		{
			parser->current = backtrack;
			return (0);
		}
		expect_and_or_suffix(parser);
		return (1);
	}
	return (0);

}

int	expect_and_or(t_parser *parser)
{
	ft_printf("function: %s\n", "and_or");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	t_token *backtrack;
	
	backtrack = parser->current;
	if (expect_pipeline(parser))
	{
		expect_and_or_suffix(parser);
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	expect_list_suffix(t_parser *parser)
{
	ft_printf("function: %s\n", "list_suffix");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	t_token *backtrack;
	
	backtrack = parser->current;
	if (expect_separator_op(parser))
	{
		if (!expect_and_or(parser))
		{
	//		ft_printf("suffix rejected\n=================\n");
			parser->current = backtrack;
			return (1);
		}
		expect_list_suffix(parser);
	}
	return (1);
}

int	expect_list(t_parser *parser)
{
	ft_printf("function: %s\n", "list");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	t_token *backtrack;

	backtrack = parser->current;
	if (expect_and_or(parser))
	{
		if (expect_list_suffix(parser))
			return (1);
	}
	parser->current = backtrack;
	return (0);
}

//top level function, no need for backtrack var
int	expect_complete_cmd(t_parser *parser)
{	
	ft_printf("function: %s\n", "complete_cmd");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	if (expect_list(parser))
	{
		if ((expect_separator(parser) || (parser->current->type == NEWLINE)))
			return (1);	
	}
	return (0);
}
