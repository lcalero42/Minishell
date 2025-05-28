/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:02:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/28 10:09:45 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_token(t_token *token, t_command **cmd_list,
				t_command **current_cmd);
static void	finalize_command_parsing(t_command *cmd_list);

void	shift_right_2d_string(char **arr)
{
	int	size;
	int	i;

	size = 0;
	while (arr[size] != NULL)
		size++;
	if (!arr || size <= 1)
		return ;
	i = size - 1;
	while (i > 0)
	{
		arr[i] = arr[i - 1];
		i--;
	}
	arr[0] = arr[size - 1];
}

t_command	*parse_commands(t_token *token_list)
{
	t_command	*cmd_list;
	t_command	*current_cmd;
	t_token		*token;

	cmd_list = NULL;
	current_cmd = NULL;
	token = token_list;
	while (token)
	{
		process_token(token, &cmd_list, &current_cmd);
		if (should_handle_redirection(token, current_cmd))
			token = token->next;
		token = token->next;
	}
	finalize_command_parsing(cmd_list);
	return (cmd_list);
}

static void	process_token(t_token *token, t_command **cmd_list,
							t_command **current_cmd)
{
	if (token->type == PIPE)
		*current_cmd = NULL;
	else if ((is_text_token(token->type))
		&& (!*current_cmd || !(*current_cmd)->command))
		handle_word_token(token, cmd_list, current_cmd);
	else if (is_text_token(token->type) && *current_cmd
		&& (*current_cmd)->command)
		add_argument(*current_cmd, token->value);
	else if (should_handle_redirection(token, *current_cmd))
		handle_redirections(token, cmd_list, current_cmd);
}

static void	finalize_command_parsing(t_command *cmd_list)
{
	if (cmd_list && cmd_list->command && ft_strchr(cmd_list->command, ' '))
		handle_command_with_spaces(cmd_list);
}
