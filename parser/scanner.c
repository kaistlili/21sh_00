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


t_token	*new_token(int	type)
{
	t_token *new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	if (!(new->data.str = ft_memalloc(INPUTSZ * sizeof(char))))
		return (NULL);
	new->data.size = INPUTSZ;
	new->type = type;
	return (new);	
}

int	str_putchar(char c, t_str *data)
{
	size_t i;

	i = data->len;
	data->str[i] = c;
	data->len = i + 1;
	if (data->len == data->size)
		if (ft_str_realloc(data, INPUTSZ) == MEMERR)
			return (MEMERR);
	return (0);	
}

int	ft_is_ifs(char c)
{
	static char *ifs = NULL;
	int			i;

	i = 0;
	if (!ifs)
		ifs = "\n\t ";
	while (ifs[i])
	{
		if (ifs[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	init_jump_table(t_func table[256])
{
	size_t i;

	i = 0;

	while (i < 256)
	{
		if ((i < 58) && (i > 47))
			table[i] = handle_digit;
		else
			table[i] = handle_common;
		i++;
	}
	table[34] = handle_dquote;
	table[38] = handle_ampersand;
	table[39] = handle_squote;
	table[59] = handle_semic;
	table[60] = handle_less;
	table[62] = handle_great;
	table[124] = handle_column;	

}

void	add_token(t_token **head, t_token *to_add)
{
	t_token *tmp;

	tmp = *head;
	if (*head == NULL)
		*head = to_add;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = to_add;	
	}
}

t_token	*ft_tokenizer(char *line)
{
	static	t_func	table[256];
	static	int		flag = 0;
	t_token			*tmp;
	t_token			*head;

	if (!flag)
		init_jump_table(table);
	flag = 1;
	head = NULL;
	while (*line)
	{
		tmp = new_token(0);
		if (!tmp)
			return (NULL);
		table[*line](&line, tmp);	
		add_token(&head, tmp);
		while (ft_is_ifs(*line))
			line++;
	}
	return (head);
}

int main(int ac, char **av)
{
	t_token *tok;

	if (av[1] == NULL)
		return (0);
	ft_printf("line %s\n", av[1]);	
	tok = ft_tokenizer(av[1]);
	while (tok)
	{
		ft_printf("type %d | str %s\n", tok->type, tok->data.str);
		tok = tok->next;
	}
}
