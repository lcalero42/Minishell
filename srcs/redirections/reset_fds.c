/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:21:19 by ekeisler          #+#    #+#             */
/*   Updated: 2025/04/17 17:18:41 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fds(t_command *cmd)
{
	if (cmd->saved_stdin != -1)
	{
		dup2(cmd->saved_stdin, STDIN_FILENO);
		close(cmd->saved_stdin);
		cmd->saved_stdin = -1;
	}
	if (cmd->saved_stdout != -1)
	{
		dup2(cmd->saved_stdout, STDOUT_FILENO);
		close(cmd->saved_stdout);
		cmd->saved_stdout = -1;
	}
}
