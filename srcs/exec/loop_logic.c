/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:14:35 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/16 15:11:43 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit(char *line);
static int	process_input(char *line, t_data *data);

void	loop(t_data *data)
{
	char	*line;
	int		process_result;
	int		result;

	while (1)
	{
		handle_signals_before_input();
		line = readline("\e[1;32mMinishell> \e[0m");
		process_result = process_input(line, data);
		result = handle_command_result(line, process_result);
		if (result == 1)
			break ;
		if (result == 2)
			continue ;
		execute_and_update(data);
		cleanup_iteration(line, data);
	}
	free_all(line, data, data->commands);
	ft_free_env(data);
	rl_clear_history();
}

void	execute_commands(t_data *data)
{
	if (!check_pipe(data))
		handle_commands(data);
	else
		exec_pipe(data);
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
