/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:14:35 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/16 14:51:34 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit(char *line);
static int	process_input(char *line, t_data *data);
static void	execute_commands(t_data *data);

void	loop(t_data *data)
{
	char	*line;
	int		process_result;

	while (1)
	{
		if (g_signals != SIGINT)
			setup_signal(0);
		else
			g_signals = 0;
		line = readline("\e[1;32mMinishell> \e[0m");
		process_result = process_input(line, data);
		if (!line)
			break ;
		if (process_result == 0)
			continue ;
		if (process_result == -1)
			break ;
		if (g_signals == SIGINT)
			data->exit_status = 130;
		setup_signal(2);
		execute_commands(data);
		if (g_signals == SIGINT)
			data->exit_status = 130;
		else if (g_signals == SIGQUIT)
			data->exit_status = 131;
		if (*line)
			add_history(line);
		free_all(line, data, data->commands);
		g_signals = 0;
	}
	free_all(line, data, data->commands);
	ft_free_env(data);
	rl_clear_history();
}

static int	process_input(char *line, t_data *data)
{
	data->tokens = tokenize(line, data);
	data->commands = parse_commands(data->tokens);
	if (!handle_exit(line))
	{
		ft_putstr_fd("exit\n", 1);
		return (-1);
	}
	if (!check_parsing_errors(line))
		return (0);
	return (1);
}

static void	execute_commands(t_data *data)
{
	if (!check_pipe(data))
		handle_commands(data);
	else
		exec_pipe(data);
}

static int	handle_exit(char *line)
{
	if (!line)
		return (0);
	return (1);
}

void	free_all(char *line, t_data *data, t_command *first_cmd)
{
	if (line)
		free(line);
	if (first_cmd)
		free_commands(first_cmd);
	if (data->tokens)
		free_tokens(data->tokens);
}
