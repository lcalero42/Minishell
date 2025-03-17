/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis <luis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:15:06 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/17 17:17:34 by luis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_operators(t_token **tokens, char *input, int *i);
static void	handle_words(t_token **tokens, t_data *data, char *input, int *i);
static void	add_word(char *input, int *i, t_token_type type, t_token **tokens);

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
	
	if (input[*i] == '$')
	{
		word = extract_word(input + *i + 1);
		if (!ft_getenv(data, word))
		{
			*i += ft_strlen(word);
			free(word);
			return ;
		}
		add_token(tokens, ft_getenv(data, word), ENV_VAR);
		*i += ft_strlen(word);
		free(word);
	}
	else if (input[*i] == '\'' || input[*i] == '"')
		add_word(extract_quoted_string(input + *i), i, QUOTE, tokens);
	else if (!ft_isspace(input[*i]))
		add_word(extract_word(input + *i), i, WORD, tokens);
}

static void	add_word(char *input, int *i, t_token_type type, t_token **tokens)
{
	char *word;

	word = input;
	add_token(tokens, word, type);
	if (type == WORD)
		*i += ft_strlen(word) - 1;
	else
	*i += ft_strlen(word) + 2;
	free(word);
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
