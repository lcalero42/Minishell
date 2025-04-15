/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:14:35 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/15 17:01:12 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_input(char *line, t_data *data);
static void	execute_commands(t_data *data);
static void	exec_reset_cmd(t_data *data, char *line);

void	loop(t_data *data)
{
	char	*line;
	int		process_result;

	while (1)
	{
		line = readline("\e[1;32mMinishell> \e[0m");
		process_result = process_input(line, data);
		if (!line)
			break ;
		if (process_result == 0)
		{
			free_all(line, data, data->commands);
			continue ;
		}
		if (process_result == -1)
		{
			free_all(line, data, data->commands);
			break ;
		}
		exec_reset_cmd(data, line);
	}
	free_all(line, data, data->commands);
	ft_free_env(data);
	rl_clear_history();
}

static void	exec_reset_cmd(t_data *data, char *line)
{
	execute_commands(data);
	if (*line)
		add_history(line);
	free_all(line, data, data->commands);
	line = NULL;
	data->commands = NULL;
	data->tokens = NULL;
}

static int	process_input(char *line, t_data *data)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		return (-1);
	}
	if (!check_parsing_errors(line))
		return (0);
	data->tokens = tokenize(line, data);
	data->commands = parse_commands(data->tokens);
	return (1);
}

static void	execute_commands(t_data *data)
{
	if (!check_pipe(data))
		handle_commands(data);
	else
		exec_pipe(data);
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
