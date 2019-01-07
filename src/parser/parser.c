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

#include "../minishell.h"


int	expect_cmd_pre(t_token *start)
{
}

int	expect_cmd_pre(t_token *start)
{
	if ((expect_io_redir(start))
		|| (start->type = ASSIGN))
	{
		if (cmd	
		return (1);
	}
}

int	expect_cmd_word(t_token *start)
{
}

int	expect_cmd_suffix(t_token *start)
{
}

int	expect_simple_cmd(t_token *start)
{
	if (expect_cmd_pre(start))
	{
		if (expect_cmd_word(next_sym(start)))
			expect_cmd_suffix(next_sym(start));
		return (1);
	}
	return (0);
}

int	expect_pipeline_suffix(t_token *start)
{
	if (start->type = PIPE)
	{
		if (!expect_linebreak(next_sym(start)))
			return (0);
		if (!expect_simple_cmd(next_sym(start)))
			return (0);
	}
	return (1);
}

int	expect_pipeline(t_token *start)
{
	if (expect_simple_cmd(start))
	{
		if (expect_pipeline_suffix(next_sym(start)))
			return (1);
	}
	return (0);
}

int	expect_or_if_suffix(t_token *start)
{
	if (start->type == OR_IF)
	{
		if (!expect_linebreak(next_sym(start)))
			return (0);
		if (!expect_pipeline(next_sym(start)))
			return (0);
		expect_or_if_suffix(next_sym(start));
	}
	return (1);
}

int	expect_and_if_suffix(t_token *start)
{
	if (start->type == AND_IF)
	{
		if (!expect_linebreak(next_sym(start)))
			return (0);
		if (!expect_pipeline(next_sym(start)))
			return (0);
		expect_and_if_suffix(next_sym(start));
	}
	return (1);
}

int	expect_and_or(t_token *start)
{
	if (expect_pipeline(start))
	{
		if ((expect_and_if_suffix(next_sym(start)))
			|| (expect_or_if_suffix(start)))
			return (1);
	}
	return (0);
}

int	expect_list(t_token *start)
{
	if ((expect_and_or(start))
		&& (expect_list_suffix(next_sym(start))))
		return (1);
	return (0);
}

int	expect_list(t_token *start)
{
	if (expect_and_or(start))
	{
		if (expect_list_suffix(next_sym(start)))
			return (1);
	}
	return (0);
}

int	expect_list_suffix(t_token *start)
{
	if (expect_separator_op(start))
	{
		if (!expect_and_or(next_sym(start)))
			return (0);
		expect_list_suffix(t_token *start);
	}
	return (1);
}

int	expect_complete_cmd(t_token *start)
{
	t_token tmp;

	if (expect_list(start))
	{
		expect_separator(next_sym(start))
		return (1);	
	}
	return (0);
}

t_token	next_sym(t_token *start)
{
	t_token *tmp;

	tmp = start;
	while (tmp->next)
		tmp = tmp->next;
	next_token(NULL, &tmp);
	return (tmp->next);
}

int	ft_parser(char *line)
{
	t_token *head;
	t_token *current;
	char	*iter;

	iter = line;
	next_token(&iter, &head);
	return(expect_complete_cmd(head));
}
