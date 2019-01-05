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

#include "ft_parser.h"
/*
add mem error exit for str_putchar
*/
int	handle_dquote(char **input, t_token *token)
{
	char *iter;

	iter = *input + 1;
	while (*iter)
	{
		if (*iter == '"')
		{
			*input = iter;
			return (0);
		}
		else if (*iter == '\\')
		{
			if (*(iter + 1) == '"')
				iter++;
		}
		else
			str_putchar(*iter, &(token->data));
		iter++;
	}
	*input = iter;
	return (DQUOTE_ERR);
}

int handle_squote(char **input, t_token *token)
{
	return (0);
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
		else if (*iter == '\\')
			iter++;
		str_putchar(*iter, &(token->data));
		iter++;
	}
	*input = iter;
	return (0);
}

int	handle_common(char **input, t_token *token)
{
	char 			*iter;
	static	char	*ops = "|&><;";

	iter = *input;
	while (*iter)
	{
		if ((ft_is_ifs(*iter)) || (ft_strchr(ops, *iter)))
			break;
		else if (*iter == '\\')
			iter++;
		str_putchar(*iter, &(token->data));
		iter++;
	}
	*input = iter;
	return (0);
}

int	handle_semic(char **input, t_token *token)
{
	token->type = SEMI_COL;
	str_putchar(**input, &(token->data));
	*input = *input + 1;
	return (0);
}	

int	handle_column(char **input, t_token *token)
{
	char *iter;

	iter = *input;
	str_putchar(*iter, &(token->data));
	if (*(iter + 1) == '|')
	{
		iter++;
		str_putchar(*iter, &(token->data));
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
	str_putchar(*iter, &(token->data));
	if (*(iter + 1) == '&')
	{
		iter++;
		str_putchar(*iter, &(token->data));
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
	str_putchar(*iter, &(token->data));
	token->type = GREAT;
	if (*(iter + 1) == '>')
	{
		iter++;
		str_putchar(*iter, &(token->data));
		token->type = DGREAT;
	}
	else if (*(iter + 1) == '&')
	{
		iter++;
		str_putchar(*iter, &(token->data));
		token->type = GREATAND;
	}
	*input = iter + 1;
	return (0);
}

int handle_less(char **input, t_token *token)
{
	char *iter;

	iter = *input;
	str_putchar(*iter, &(token->data));
	token->type = LESS;
	if (iter[1] == '&')
	{
		iter++;
		str_putchar(*iter, &(token->data));
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
