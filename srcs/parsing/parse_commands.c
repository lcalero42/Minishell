/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:02:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/27 19:46:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_handle_redirection(t_token *token, t_command *cmd);
static int	is_text_token(t_token_type type);
static void	handle_redirections(t_token *token, t_command **cmd_list,
				t_command **current_cmd);
static void	handle_word_token(t_token *token, t_command **cmd_list,
				t_command **current_cmd);


void shift_right_2d_string(char **arr)
{
	int size = 0;
	while (arr[size] != NULL)
        size++;
	
	if (!arr || size <= 1)
		return ;
	for (int i = size - 1; i > 0; i--)
		arr[i] = arr[i - 1];
	arr[0] = arr[size - 1];
}

t_command	*parse_commands(t_token *token_list)
{
	t_command		*cmd_list;
	t_command		*current_cmd;
	t_token			*token;

	cmd_list = NULL;
	current_cmd = NULL;
	token = token_list;
	while (token)
	{
		if (token->type == PIPE)
			current_cmd = NULL;
		else if ((is_text_token(token->type))
			&& (!current_cmd || !current_cmd->command))
			handle_word_token(token, &cmd_list, &current_cmd);
		else if (is_text_token(token->type) && current_cmd
			&& current_cmd->command)
			add_argument(current_cmd, token->value);
		else if (should_handle_redirection(token, current_cmd))
		{
			handle_redirections(token, &cmd_list, &current_cmd);
			token = token->next;
		}
		token = token->next;
	}
	if (cmd_list->command)
	{
		if (ft_strchr(cmd_list->command, ' '))
		{
			char	**cmd_split = ft_split(cmd_list->command, ' ');
			int		split_size = count_args(cmd_split);
			int		existing_args = count_args(current_cmd->args);
			
			current_cmd = cmd_list;
			free(current_cmd->command);
			current_cmd->command = ft_strdup(cmd_split[0]);
			char **new_args = malloc((existing_args + split_size - 1 + 1) * sizeof(char*));
			int i = 0;
			for (int j = 1; j < split_size; j++)
			{
				new_args[i] = ft_strdup(cmd_split[j]);
				i++;
			}
			for (int j = 0; j < existing_args; j++)
			{
				new_args[i] = current_cmd->args[j];
				i++;
			}
			new_args[i] = NULL;
			free(current_cmd->args);
			current_cmd->args = new_args;
			
			ft_free(cmd_split);
		}
	}
	return (cmd_list);
}

static void	handle_redirections(t_token *token, t_command **cmd_list,
								t_command **current_cmd)
{
	t_redir_type	type;
	t_command		*new_cmd;

	if (!(*current_cmd))
	{
		new_cmd = init_command();
		if (!(*cmd_list))
			*cmd_list = new_cmd;
		else
			add_command(cmd_list, new_cmd);
		*current_cmd = new_cmd;
	}
	if (token->type == REDIR_IN)
		type = REDIR_INPUT;
	else if (token->type == REDIR_OUT)
		type = REDIR_OUTPUT;
	else if (token->type == REDIR_APPEND)
		type = REDIR_APPEND_OUT;
	else
		type = REDIR_HEREDOC;
	add_redirection(*current_cmd, token->next->value, type);
}

static void	handle_word_token(t_token *token, t_command **cmd_list,
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

static int	should_handle_redirection(t_token *token, t_command *cmd)
{
	(void)cmd;
	return ((token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == HEREDOC)
		&& token->next && (token->next->type == WORD
			|| token->next->type == QUOTE || token->next->type == ENV_VAR));
}

static int	is_text_token(t_token_type type)
{
	return (type == WORD || type == QUOTE || type == ENV_VAR);
}
