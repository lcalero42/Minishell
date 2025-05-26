/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:07:09 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/26 16:26:53 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	handle_input_output(int fd, t_redirection *redir);
static int	handle_heredoc(t_redirection *redir);
static int	handle_append_out(int fd, t_redirection *redir);

int	apply_redirections(t_command *cmd, t_data *data)
{
	t_redirection	*redir;
	int				fd;

	fd = -1;
	cmd->saved_stdin = dup(STDIN_FILENO);
	cmd->saved_stdout = dup(STDOUT_FILENO);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_INPUT || redir->type == REDIR_OUTPUT)
			fd = handle_input_output(fd, redir);
		else if (redir->type == REDIR_APPEND_OUT)
			fd = handle_append_out(fd, redir);
		else if (redir->type == REDIR_HEREDOC)
			fd = handle_heredoc(redir);
		if (fd > 2)
			close(fd);
		else if (fd == -1)
		{
			data->exit_status = 1;
			return (0);
		}
		redir = redir->next;
	}
	return (1);
}

static int	handle_input_output(int fd, t_redirection *redir)
{
	if (redir->type == REDIR_INPUT)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			perror(redir->file);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_OUTPUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(redir->file);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (fd);
}

static int	handle_heredoc(t_redirection *redir)
{
	if (redir->heredoc_fd >= 0)
	{
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
		return (0);
	}
	return (-1);
}

static int	handle_append_out(int fd, t_redirection *redir)
{
	if (redir->type == REDIR_APPEND_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(redir->file);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (fd);
}
