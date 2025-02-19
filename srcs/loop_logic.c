/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:25:23 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 19:28:51 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_exit(char *line);

void	loop(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("\e[1;32mMinishell> \e[0m");
		pars_input(data, line);
		if (!handle_exit(line))
			break ;
		handle_commands(data);
		if (*line)
			add_history(line);
		free(line);
		ft_free(data->cmd);
	}
	free(line);
	if (line)
		ft_free(data->cmd);
	rl_clear_history();
}

static int	handle_exit(char *line)
{
	if (!line)
		return (0);
	if (!ft_strncmp("exit", line, 4))
		return (0);
	return (1);
}
