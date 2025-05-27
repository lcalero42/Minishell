/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:14:35 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/27 16:15:57 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_sigint(t_data *data);
static int	process_input(char *line, t_data *data);

void	loop(t_data *data)
{
	char	*line;
	int		process_result;
	int		result;
	char	*prompt;

	while (1)
	{
		handle_signals_before_input();
		prompt = get_prompt_line(data);
		line = readline(prompt);
		free(prompt);
		check_sigint(data);
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
	if (data->can_exec == 1)
	{
		if (!check_pipe(data))
			handle_commands(data);
		else
			exec_pipe(data);
	}
}

static int	process_input(char *line, t_data *data)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		return (-1);
	}
	data->raw_line = line;
	if (!check_parsing_errors(line, data))
		return (0);
	data->tokens = tokenize(line, data);
	if (!check_syntax(data))
	{
		data->exit_status = 2;
		free_tokens(data->tokens);
		data->tokens = NULL;
		add_history(line);
		return (0);
	}
	data->commands = parse_commands(data->tokens);
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

static void	check_sigint(t_data *data)
{
	if (g_signals == SIGINT)
	{
		data->exit_status = 130;
		g_signals = 0;
	}
}
