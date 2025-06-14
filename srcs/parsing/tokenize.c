/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:15:06 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/14 14:56:43 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_operators(t_token **tokens, char *input, int *i);
static void	handle_words(t_token **tokens, t_data *data, char *input, int *i);
static void	add_word(char *input, t_token_type type, t_token **tokens);

t_token	*tokenize(char *input, t_data *data)
{
	t_token	*tokens;
	int		i;

	if (!input)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (handle_operators(&tokens, input, &i))
		{
			i++;
			continue ;
		}
		handle_words(&tokens, data, input, &i);
		i++;
	}
	return (tokens);
}

static int	handle_operators(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '|')
		add_token(tokens, "|", PIPE);
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, "<<", HEREDOC);
		*i += 1;
	}
	else if (input[*i] == '<')
		add_token(tokens, "<", REDIR_IN);
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, ">>", REDIR_APPEND);
		*i += 1;
	}
	else if (input[*i] == '>')
		add_token(tokens, ">", REDIR_OUT);
	if (input[*i] == '|' || (input[*i] == '<' && input[*i + 1] == '<')
		|| input[*i] == '<' || (input[*i] == '>' && input[*i + 1] == '>')
		|| input[*i] == '>')
		return (1);
	return (0);
}

static void	handle_words(t_token **tokens, t_data *data, char *input, int *i)
{
	char	*word;
	char	*tmp_word;

	if (input[*i] == '$')
	{
		tmp_word = extract_word(input + *i);
		word = interpreter_word(i, tmp_word, data, 1);
		add_token(tokens, word, ENV_VAR);
		free(word);
		free(tmp_word);
	}
	else if (input[*i] == '\'' || input[*i] == '"')
	{
		word = extract_word(input + *i);
		add_word(interpreter_word(i, word, data, 1), QUOTE, tokens);
		free(word);
	}
	else if (!ft_isspace(input[*i]))
	{
		word = extract_word(input + *i);
		add_word(interpreter_word(i, word, data, 1), WORD, tokens);
		free(word);
	}
}

static void	add_word(char *input, t_token_type type, t_token **tokens)
{
	add_token(tokens, input, type);
	free(input);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
}
