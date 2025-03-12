/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:25:23 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/12 15:10:27 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit(char *line);

void	loop(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("\e[1;32mMinishell> \e[0m");
		data->tokens = tokenize(line, data);
		if (!handle_exit(line))
			break ;
		while (data->tokens)
		{
			printf("value : %s\n", data->tokens->value);
			printf("type : %d\n", data->tokens->type);
			data->tokens = data->tokens->next;
		}
		// handle_commands(data);
		if (*line)
			add_history(line);
		free(line);
		ft_free(data->cmd);
	}
	free(line);
	ft_free_env(data);
	if (line)
		ft_free(data->cmd);
	rl_clear_history();
}

static int	handle_exit(char *line)
{
	if (!line)
		return (0);
	return (1);
}
