/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:14:54 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/14 17:53:23 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_syntax(t_token *token);
static int	check_redir_syntax(t_token *token);
static int	check_adjacent_tokens(t_token *token);

static int	check_pipe_syntax(t_token *token)
{
	t_token	*next;

	next = token->next;
	if (token->type == PIPE)
	{
		if (!token->next)
			return (0);
		next = token->next;
		if (next->type == PIPE)
			return (0);
	}
	return (1);
}

static int	check_redir_syntax(t_token *token)
{
	t_token	*next;

	next = token->next;
	if (token->type == REDIR_APPEND || token->type == REDIR_IN
		|| token->type == HEREDOC || token->type == REDIR_OUT)
	{
		if (!token->next)
			return (0);
		next = token->next;
		if (next->type == PIPE || next->type == REDIR_APPEND
			|| next->type == REDIR_IN || next->type == HEREDOC
			|| next->type == REDIR_OUT)
			return (0);
	}
	return (1);
}

static int	check_adjacent_tokens(t_token *token)
{
	t_token_type	current_type;
	t_token_type	next_type;

	current_type = token->type;
	if (token->next && (current_type == PIPE || current_type == REDIR_APPEND || 
			current_type == REDIR_IN || current_type == HEREDOC ||
			current_type == REDIR_OUT))
	{
		next_type = token->next->type;
		if (next_type == PIPE && current_type == PIPE)
			return (0);
	}
	return (1);
}

int	check_syntax(t_data *data)
{
	t_token	*token;

	if (!data->tokens)
		return (1);
	token = data->tokens;
	if (token->type == PIPE)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token '|'\n", 2);
		return (0);
	}
	while (token)
	{
		if (!check_pipe_syntax(token))
			ft_putstr_fd("Minishell: syntax error near unexpected token '|'\n", 2);
		else if (!check_redir_syntax(token))
			ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		else if (!check_adjacent_tokens(token))
			ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		if (!check_pipe_syntax(token) || !check_redir_syntax(token)
			|| !check_adjacent_tokens(token))
			return (0);
		token = token->next;
	}
	return (1);
}
