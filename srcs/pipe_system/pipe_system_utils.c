/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_system_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:55:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/26 16:08:57 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_data *data)
{
	t_token *token = data->tokens;

	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void	wait_processes(t_data *data, int *status)
{
	*status = 0;
	while (waitpid(-1, status, 0) > 0)
	{
		if (WIFEXITED(*status))
			data->exit_status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			data->exit_status = 128 + WTERMSIG(*status);
	}
}
