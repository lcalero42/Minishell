/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:07:09 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/24 13:48:25 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	apply_redirections(t_command *cmd)
{
	t_redirection	*redir;
	int				fd;

	cmd->saved_stdin = dup(STDIN_FILENO);
	cmd->saved_stdout = dup(STDOUT_FILENO);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_INPUT)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
			{
				perror(redir->file);
				return (0);
			}
			dup2(fd, STDIN_FILENO);
		}
		else if (redir->type == REDIR_OUTPUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(redir->file);
				return (0);
			}
			dup2(fd, STDOUT_FILENO);
		}
		else if (redir->type == REDIR_APPEND_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(redir->file);
				return (0);
			}
			dup2(fd, STDOUT_FILENO);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			fd = handle_heredoc(redir->file);
			if (fd == -1)
				return (0);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (1);
}

void	reset_fds(t_command *cmd)
{
	if (cmd->saved_stdin != -1)
	{
		dup2(cmd->saved_stdin, STDIN_FILENO);
		close(cmd->saved_stdin);
	}
	if (cmd->saved_stdout != -1)
	{
		dup2(cmd->saved_stdout, STDOUT_FILENO);
		close(cmd->saved_stdout);
	}
}
