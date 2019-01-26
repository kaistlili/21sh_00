/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 20:21:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


/*
int	field_split(t_token *word)
{

}

int	expand_param(t_token *word)
{
}

	upadte lexer to recognise ${ and prompt for newline when ${ has no matching } done
	nested backslash, squote and dquote in {} is "bad substitution" done
	any invalid assign name is bad substitution done

dont forget $ followed by \0 is like quoted

*/
/*
int	expand_params(t_token *word)
{
	int index;
	int	move;
	char *value;

	index = 0;
	move = 0;
	while (word->data.str[index])
	{
		if ((word->data.str[index] == '$') && (word->data.str[index + 1] != 0))
		{
			
				
		}
	}
}
*/

int	ft_wordexp(t_token *word)
{
	if (handle_tilde(word) == MEMERR)
		return (MEMERR);
	
	return (0);
}
