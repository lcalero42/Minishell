/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:14:35 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/25 16:22:25 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit(char *line);

void	loop(t_data *data)
{
	char		*line;

	while (1)
	{
		line = readline("\e[1;32mMinishell> \e[0m");
		data->tokens = tokenize(line, data);
		data->commands = parse_commands(data->tokens);
		if (!handle_exit(line))
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (!check_pipe(data))
			handle_commands(data);
		else
			exec(data);
		if (*line)
			add_history(line);
		free_all(line, data, data->commands);
	}
	free_all(line, data, data->commands);
	ft_free_env(data);
	rl_clear_history();
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
