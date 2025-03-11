/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:25:23 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/10 15:17:26 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit(char *line);

void	loop(t_data *data, t_token *token)
{
	char	*line;

	while (1)
	{
		line = readline("\e[1;32mMinishell> \e[0m");
		token = tokenize(line, data);
		if (!handle_exit(line))
			break ;
		while (token)  // Parcours toute la liste, y compris le dernier élément
		{
			printf("value : %s\n", token->value);
			printf("type : %d\n", token->type);
			token = token->next;
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
