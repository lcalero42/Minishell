/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:15:06 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/10 17:29:32 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *input, t_data *data)
{
	t_token	*tokens;
	int	i;

	tokens = NULL;
	i = 0;
	
	while (input[i])
	{
		if (input[i] == '|')
			add_token(&tokens, '|', PIPE);
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token(&tokens, "<<", HEREDOC);
			i++;
		}
		else if (input[i] == '<')
			add_token(&tokens, "<", REDIR_IN);
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(&tokens, ">>", REDIR_APPEND);
			i++;
		}
		else if (input[i] == '>')
			add_token(&tokens, ">", REDIR_OUT);
		else if (input[i] == '$')
			add_token(&tokens, ft_getenv(data, extract_word(input[i] + i)), ENV_VAR);
		else if (input[i] == '\'' || input[i] == '"')
			add_token(&tokens, extract_quoted_string(input + i), QUOTE);
		else if (!ft_isspace(input[i]))
			add_token(&tokens, extract_word(input[i] + i), WORD);
		i++;
	}
	return (tokens);
}
