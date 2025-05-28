/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:07:46 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/28 10:14:35 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	get_redirection_type(t_token_type type);
static t_command	*create_new_command_if_needed(t_command **cmd_list,
						t_command **current_cmd);

void	handle_redirections(t_token *token, t_command **cmd_list,
						t_command **current_cmd)
{
	t_redir_type	type;

	if (!(*current_cmd))
		*current_cmd = create_new_command_if_needed(cmd_list, current_cmd);
	type = get_redirection_type(token->type);
	add_redirection(*current_cmd, token->next->value, type);
}

void	handle_word_token(t_token *token, t_command **cmd_list,
						t_command **current_cmd)
{
	t_command	*new_cmd;

	if (*current_cmd && !(*current_cmd)->command)
	{
		(*current_cmd)->command = ft_strdup(token->value);
		return ;
	}
	new_cmd = init_command();
	if (!new_cmd)
		return ;
	new_cmd->command = ft_strdup(token->value);
	if (!new_cmd->command)
	{
		free_commands(new_cmd);
		return ;
	}
	if (!(*cmd_list))
		*cmd_list = new_cmd;
	else
		add_command(cmd_list, new_cmd);
	*current_cmd = new_cmd;
}

static t_redir_type	get_redirection_type(t_token_type type)
{
	if (type == REDIR_IN)
		return (REDIR_INPUT);
	else if (type == REDIR_OUT)
		return (REDIR_OUTPUT);
	else if (type == REDIR_APPEND)
		return (REDIR_APPEND_OUT);
	else
		return (REDIR_HEREDOC);
}

static t_command	*create_new_command_if_needed(t_command **cmd_list,
												t_command **current_cmd)
{
	t_command	*new_cmd;

	(void)current_cmd;
	new_cmd = init_command();
	if (!(*cmd_list))
		*cmd_list = new_cmd;
	else
		add_command(cmd_list, new_cmd);
	return (new_cmd);
}

int	should_handle_redirection(t_token *token, t_command *cmd)
{
	(void)cmd;
	return ((token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == HEREDOC)
		&& token->next && (token->next->type == WORD
			|| token->next->type == QUOTE || token->next->type == ENV_VAR));
}
