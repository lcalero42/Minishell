/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:07:09 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/27 14:31:37 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	handle_input_output(int fd, t_redirection *redir);
static int	handle_heredoc(int fd, t_redirection *redir);
static int	handle_append_out(int fd, t_redirection *redir);

// fixing
int	apply_redirections(t_command *cmd)
{
	t_redirection	*redir;
	int				fd;

	fd = 0;
	cmd->saved_stdin = dup(STDIN_FILENO);
	cmd->saved_stdout = dup(STDOUT_FILENO);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_INPUT)
			handle_input_output(fd, redir);
		else if (redir->type == REDIR_OUTPUT)
			handle_input_output(fd, redir);
		else if (redir->type == REDIR_APPEND_OUT)
			handle_append_out(fd, redir);
		else if (redir->type == REDIR_HEREDOC)
			handle_heredoc(fd, redir);
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
			return (0);
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
			return (0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

static int	handle_heredoc(int fd, t_redirection *redir)
{
	if (redir->type == REDIR_HEREDOC)
	{
		fd = apply_heredoc(redir->file);
		if (fd == -1)
			return (0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

static int	handle_append_out(int fd, t_redirection *redir)
{
	if (redir->type == REDIR_APPEND_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(redir->file);
			return (0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}