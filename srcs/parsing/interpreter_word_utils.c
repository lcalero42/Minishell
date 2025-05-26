/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_word_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:52:05 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 12:10:46 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_char(char *word, size_t *j, char **rslt);

int	process_quotes_and_vars(char *word, size_t *j,
							char **rslt, t_data *data)
{
	size_t	new_j;

	if (word[*j] == '"' || word[*j] == '\'')
	{
		new_j = interpreter_quotes(word, *j, rslt, data);
		if (new_j == 0)
			return (0);
		*j = new_j;
	}
	else if (word[*j] == '$')
		*j = handle_env_vars(word, *j, rslt, data);
	else
	{
		add_char_to_result(rslt, word[*j]);
		(*j)++;
	}
	return (1);
}

int	process_word_chars(char *word, t_data *data,
							char **rslt, int read_quotes)
{
	size_t	j;

	j = 0;
	while (word[j])
	{
		if ((word[j] == '"' || word[j] == '\'') && !read_quotes)
		{
			if (!process_char(word, &j, rslt))
				return (0);
		}
		else if (!process_quotes_and_vars(word, &j, rslt, data))
			return (0);
	}
	return (1);
}

static int	process_char(char *word, size_t *j, char **rslt)
{
	add_char_to_result(rslt, word[*j]);
	(*j)++;
	return (1);
}
