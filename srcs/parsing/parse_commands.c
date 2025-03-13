/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:02:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/13 18:23:44 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redirection(t_command *cmd, char *file, t_redir_type type);

t_command *parse_commands(t_token *token_list)
{
	t_command *cmd_list;
	t_command *current_cmd;
	t_token *token;
	
	cmd_list = NULL;
	current_cmd = NULL;
	token = token_list;
	while (token)
	{
		if (token->type == PIPE)
			current_cmd = NULL;
		else if (token->type == WORD && !current_cmd)
		{
			t_command *new_cmd = init_command();
			if (!new_cmd)
				return (free_commands(cmd_list), NULL);
			if (!cmd_list)
				cmd_list = new_cmd;
			else
				add_command(&cmd_list, new_cmd);
			current_cmd = new_cmd;
			current_cmd->command = ft_strdup(token->value);
		}
		else if (token->type == WORD && current_cmd && current_cmd->command)
			add_argument(current_cmd, token->value);
		else if ((token->type == REDIR_IN || token->type == REDIR_OUT || 
				token->type == REDIR_APPEND || token->type == HEREDOC) && 
				token->next && token->next->type == WORD)
		{
			if (current_cmd)
			{
				t_redir_type type;
				if (token->type == REDIR_IN)
					type = REDIR_INPUT;
				else if (token->type == REDIR_OUT)
					type = REDIR_OUTPUT;
				else if (token->type == REDIR_APPEND)
					type = REDIR_APPEND_OUT;
				else
					type = REDIR_HEREDOC;
				add_redirection(current_cmd, token->next->value, type);
			}
			token = token->next;
		}
		token = token->next;
	}
	return (cmd_list);
}

static void	add_redirection(t_command *cmd, char *file, t_redir_type type)
{
	t_redirection	*new_redir;
	t_redirection	*last;
	
	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return ;
	last = NULL;
	new_redir->file = ft_strdup(file);
	new_redir->type = type;
	new_redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}
