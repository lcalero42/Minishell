/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:02:42 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/26 16:56:48 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals_before_input(void)
{
	if (g_signals != SIGINT)
		setup_signal(0);
	else
		g_signals = 0;
}

int	handle_command_result(char *line, int process_result)
{
	if (!line)
		return (1);
	if (process_result == 0)
		return (2);
	if (process_result == -1)
		return (1);
	return (0);
}

void	update_exit_status(t_data *data)
{
	if (g_signals == SIGINT)
		data->exit_status = 130;
	else if (g_signals == SIGQUIT)
		data->exit_status = 131;
	g_signals = 0;
}

void	execute_and_update(t_data *data)
{
	if (g_signals == SIGINT)
	{
		data->exit_status = 130;
		g_signals = 0;
	}
	setup_signal(2);
	execute_commands(data);
	update_exit_status(data);
}

void	cleanup_iteration(char *line, t_data *data)
{
	if (*line)
		add_history(line);
	free_all(line, data, data->commands);
	line = NULL;
	data->commands = NULL;
	data->tokens = NULL;
}
