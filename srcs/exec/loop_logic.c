/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:25:23 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/14 17:04:54 by lcalero          ###   ########.fr       */
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
		handle_commands(data);
		if (*line)
			add_history(line);
		free(line);
		free_commands(data->commands);
	}
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
