/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:26:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/24 15:43:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec(t_data *data)
{
	t_command	*cmd;
	int			fd[2];
	pid_t		pid;
	int			is_known;
	
	cmd = data->commands;
	is_known = 1;
	while (cmd)
	{
		if (cmd->next)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				find_command(cmd, data, &is_known);
			}
		}
	}
}
