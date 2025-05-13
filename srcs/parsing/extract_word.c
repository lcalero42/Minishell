/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:09:33 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/13 14:08:54 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special_char(char c);
static int	handle_quotes(char c, int *in_quotes, int *quote_char);
static int	word_size(char *str);
static char	*create_word(char *str, int size);

char	*extract_word(char *str)
{
	int	size;

	size = word_size(str);
	return (create_word(str, size));
}

static int	is_special_char(char c)
{
	return (ft_isspace(c) || c == '|' || c == '<' || c == '>');
}

static int	handle_quotes(char c, int *in_quotes, int *quote_char)
{
	if ((c == '"' || c == '\'') && (!(*in_quotes) || c == *quote_char))
	{
		if (!(*in_quotes))
			*quote_char = c;
		*in_quotes = !(*in_quotes);
	}
	return (0);
}

static int	word_size(char *str)
{
	int	size;
	int	in_quotes;
	int	quote_char;

	size = 0;
	in_quotes = 0;
	quote_char = 0;
	while (str[size])
	{
		handle_quotes(str[size], &in_quotes, &quote_char);
		if (!in_quotes && is_special_char(str[size]))
			break ;
		size++;
	}
	return (size);
}

static char	*create_word(char *str, int size)
{
	char	*rslt;
	int		i;

	rslt = malloc(sizeof(char) * (size + 1));
	if (!rslt)
		return (NULL);
	i = 0;
	while (i < size)
	{
		rslt[i] = str[i];
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}
