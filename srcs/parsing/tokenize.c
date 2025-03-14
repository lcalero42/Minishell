/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:15:06 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/14 16:49:39 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_operators(t_token **tokens, char *input, int *i);
static void	handle_words(t_token **tokens, t_data *data, char *input, int *i);

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

	word = NULL;
	if (input[*i] == '$')
	{
		if (!ft_getenv(data, extract_word(input + *i + 1)))
		{
			*i += ft_strlen(extract_word(input + *i + 1));
			return ;
		}
		add_token(tokens, ft_getenv(data, extract_word(input + *i + 1)),
			ENV_VAR);
		*i += ft_strlen(extract_word(input + *i + 1));
	}
	else if (input[*i] == '\'' || input[*i] == '"')
	{
		add_token(tokens, extract_quoted_string(input + *i), QUOTE);
		*i += ft_strlen(extract_quoted_string(input + *i)) + 2;
	}
	else if (!ft_isspace(input[*i]))
	{
		add_token(tokens, extract_word(input + *i), WORD);
		*i += ft_strlen(extract_word(input + *i)) - 1;
	}
}
