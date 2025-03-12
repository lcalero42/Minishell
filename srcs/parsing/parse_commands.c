/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:02:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/12 17:41:51 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_command_to_list(t_command **cmd_list, t_command *new_cmd);
static int	count_args(t_token *tokens);

t_command	*add_commands(t_command **command, )
{
	t_command	*tmp;
	t_command	*new;

	new = malloc(sizeof(t_command));
	new->
}

static void	add_command_to_list(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*tmp;

	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return;
	}
	tmp = *cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

static int	count_args(t_token *tokens)
{
	int count = 0;

	while (tokens && tokens->type == WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}
