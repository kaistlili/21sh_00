/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_lexer.h"
/*
add mem error exit for str_putchar

when dquote or squtote is incomplete, somehow we free in add_token
*/
int	handle_dquote(char **input, t_token *token)
{
	char *iter;

	iter = *input;
	if (*iter == '"')
	{
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		iter++;
	}
	while (*iter)
	{
		if (*iter == '"')
		{
			if (str_putchar(*iter, &(token->data)) == MEMERR)
				return (MEMERR);
			*input = iter + 1;
			handle_common(input, token);
			return (0);
		}
		else if ((*iter == '\\') && (*(iter + 1)))
		{
			if (str_putchar(*iter, &(token->data)) == MEMERR)
				return (MEMERR);
			iter++;
		}
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		iter++;
	}
	*input = iter;
	return (DQUOTE_ERR);
}

int handle_squote(char **input, t_token *token)
{
	while (**input)
	{
		if (str_putchar(**input, &(token->data)) == MEMERR)
			return (MEMERR);
		if (**input == '\'')
		{
			*input = *input + 1;
			return (0);
		}
		*input = *input + 1;
	}
	return (SQUOTE_ERR);
}

int	handle_digit(char **input, t_token *token)
{
	char 			*iter;
	static	char	*ops = "|&><;";

	iter = *input;
	while (*iter)
	{
		if ((ft_is_ifs(*iter)) || (ft_strchr(ops, *iter)))
		{
			if (ft_strchr("><", *iter))
				token->type = IO_NUM;
			break;
		}
		else if ((*iter == '\\') && (*(iter + 1)))
		{
			if (str_putchar(*iter, &(token->data)) == MEMERR)
				return (MEMERR);
			iter++;
		}
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		iter++;
	}
	*input = iter;
	return (0);
}

int	handle_common(char **input, t_token *token)
{
	char 			*iter;
	int				err_ret;
	static	char	*ops = "|&><;";

	iter = *input;
	err_ret = 0;
	while (*iter)
	{
		*input = iter; /*c'est moche ca */
		if (*iter == '"')
			err_ret = handle_dquote(&iter, token);
		else if (*iter == '\'')
			err_ret = handle_squote(&iter, token);
		if (err_ret)
			return (err_ret);
		if ((ft_is_ifs(*iter)) || (ft_strchr(ops, *iter)))
			break;
		else if ((*iter == '\\') && (*(iter + 1)))
		{
			if (str_putchar(*iter, &(token->data)) == MEMERR)
				return (MEMERR);
			iter++;
		}
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		iter++;
	}
	*input = iter;
	return (0);
}

int	handle_semic(char **input, t_token *token)
{
	token->type = SEMI_COL;
	if (str_putchar(**input, &(token->data)) == MEMERR)
		return (MEMERR);
	*input = *input + 1;
	return (0);
}	

int	handle_column(char **input, t_token *token)
{
	char *iter;

	iter = *input;
	if (str_putchar(*iter, &(token->data)) == MEMERR)
		return (MEMERR);
	if (*(iter + 1) == '|')
	{
		iter++;
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = OR_IF;
	}
	else
		token->type = PIPE;
	*input = iter + 1;
	return (0);
}	

int	handle_ampersand(char **input, t_token *token)
{
	char *iter;

	iter = *input;
	if (str_putchar(*iter, &(token->data)) == MEMERR)
		return (MEMERR);
	if (*(iter + 1) == '&')
	{
		iter++;
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = AND_IF;
	}
	else
		token->type = AMPERS;
	*input = iter + 1;
	return (0);
}	

int	handle_great(char **input, t_token *token)
{
	char *iter;

	iter = *input;
	if (str_putchar(*iter, &(token->data)) == MEMERR)
		return (MEMERR);
	token->type = GREAT;
	if (*(iter + 1) == '>')
	{
		iter++;
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = DGREAT;
	}
	else if (*(iter + 1) == '&')
	{
		iter++;
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = GREATAND;
	}
	*input = iter + 1;
	return (0);
}

int handle_less(char **input, t_token *token)
{
	char *iter;

	iter = *input;
	if (str_putchar(*iter, &(token->data)) == MEMERR)
		return (MEMERR);
	token->type = LESS;
	if (iter[1] == '&')
	{
		iter++;
		if (str_putchar(*iter, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = LESSAND;
	}
/*	else if (iter[1] == '<')
	{
		iter++;
		token->type = DLESS; //heredoc
	}*/
	*input = iter + 1;
	return (0);
}
