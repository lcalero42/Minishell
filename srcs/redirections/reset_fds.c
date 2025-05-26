/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:21:19 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/19 13:18:16 by lcalero          ###   ########.fr       */
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

void	reset_all_fds(t_command *cmd)
{
	reset_all_heredocs(cmd);
	reset_fds(cmd);
}
