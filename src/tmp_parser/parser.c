/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
int	expect_cmd_pre(t_token *parser)
{
}

int	expect_cmd_pre(t_token *parser)
{
	if ((expect_io_redir(parser))
		|| (parser->type = ASSIGN))
	{
		if (cmd	
		return (1);
	}
}

int	expect_cmd_word(t_token *parser)
{
}

int	expect_cmd_suffix(t_token *parser)
{
}

int	expect_simple_cmd(t_token *parser)
{
	t_token *backtrack;
	
	if (expect_cmd_pre(parser))
	{
		if (expect_cmd_word(next_sym(parser)))
			expect_cmd_suffix(next_sym(parser));
		return (1);
	}
	return (0);
}

int	expect_pipeline_suffix(t_token *parser)
{
	t_token *backtrack;

	if (parser->type = PIPE)
	{
		if (!expect_linebreak(next_sym(parser)))
			return (0);
		if (!expect_simple_cmd(next_sym(parser)))
			return (0);
	}
	return (1);
}

int	expect_pipeline(t_token *parser)
{
	t_token *backtrack;

	if (expect_simple_cmd(parser))
	{
		if (expect_pipeline_suffix(next_sym(parser)))
			return (1);
	}
	return (0);
}

int	expect_or_if_suffix(t_token *parser)
{
	t_token *backtrack;

	if (parser->type == OR_IF)
	{
		if (!expect_linebreak(next_sym(parser)))
			return (0);
		if (!expect_pipeline(next_sym(parser)))
			return (0);
		expect_or_if_suffix(next_sym(parser));
	}
	return (1);
}

int	expect_and_if_suffix(t_token *parser)
{
	t_token *backtrack;

	if (parser->type == AND_IF)
	{
		if (!expect_linebreak(next_sym(parser)))
			return (0);
		if (!expect_pipeline(next_sym(parser)))
			return (0);
		expect_and_if_suffix(next_sym(parser));
	}
	return (1);
}

int	expect_and_or(t_token *parser)
{
	t_token *backtrack;
	
	if (expect_pipeline(parser))
	{
		if ((expect_and_if_suffix(next_sym(parser)))
			|| (expect_or_if_suffix(parser)))
			return (1);
	}
	return (0);
}

int	expect_list(t_token *parser)
{
	t_token *backtrack;
	
	if ((expect_and_or(parser))
		&& (expect_list_suffix(next_sym(parser))))
		return (1);
	return (0);
}


int	expect_list_suffix(t_token *parser)
{
	t_token *backtrack;
	
	if (expect_separator_op(parser))
	{
		if (!expect_and_or(next_sym(parser)))
			return (0);
		expect_list_suffix(t_token *parser);
	}
	return (1);
}

int	expect_list(t_token *parser)
{
	t_token *backtrack;
	
	backtrack = parser->current;
	if (expect_and_or(parser))
	{
		if (expect_list_suffix(next_sym(parser)))
			return (1);
	}
	return (0);
}

//top level function, no need for backtrack var
int	expect_complete_cmd(t_token *parser)
{	
	if (expect_list(parser))
	{
		expect_separator(next_sym(parser))
		return (1);	
	}
	return (0);
}

t_token	next_sym(t_token *parser)
{

	t_token *tmp;
	
	tmp = parser;
	while (tmp->next)
		tmp = tmp->next;
	next_token(NULL, &tmp);
	return (tmp->next);
}
*/
int	ft_parser(char *line)
{
	t_parser	parser;
	t_token		*current;
	char		*iter;

	iter = line;
	next_token(&iter, &(parser.head));
//	return(expect_complete_cmd(&parser));
}
