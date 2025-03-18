/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/18 18:35:51 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "minishell.h"

static int	handle_exit(char *line);

void	loop(t_data *data)
{
	char		*line;
	t_command	*first_cmd;

	while (1)
	{
		line = readline("\e[1;32mMinishell> \e[0m");
		data->tokens = tokenize(line, data);
		data->commands = parse_commands(data->tokens);
		first_cmd = data->commands;
		if (!handle_exit(line))
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		handle_commands(data);
		if (*line)
			add_history(line);
		free(line);
		free_commands(first_cmd);
		free_tokens(data->tokens);
	}
	free_commands(first_cmd);
	free_tokens(data->tokens);
	free(line);
	ft_free_env(data);
	rl_clear_history();
}

static int	handle_exit(char *line)
{
	if (!line)
		return (0);
	return (1);
}
