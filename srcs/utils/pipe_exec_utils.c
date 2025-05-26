/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:39:31 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/14 10:46:53 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_heredocs_for_command(t_command *cmd);

int	fork_commands(t_data *data, pid_t *pids, int num_commands)
{
	t_command	*cmd;
	int			fd[2];
	pid_t		pid;
	int			fd_in;
	int			i;

	cmd = data->commands;
	fd_in = STDIN_FILENO;
	process_all_heredocs(cmd, data);
	i = 0;
	while (cmd && i < num_commands)
	{
		pid = create_child_process(cmd, data, fd_in, fd);
		if (pid < 0)
		{
			perror("fork");
			return (0);
		}
		pids[i++] = pid;
		close_heredocs_for_command(cmd);
		fd_in = manage_parent_fd(fd_in, fd, cmd);
		cmd = cmd->next;
	}
	return (1);
}

pid_t	create_child_process(t_command *cmd, t_data *data,
	int fd_in, int *fd)
{
	pid_t	pid;

	pid = create_pipe_and_fork(fd, cmd);
	if (pid == 0)
	{
		free(data->pids);
		execute_child_process(cmd, data, fd_in, fd);
	}
	return (pid);
}

static void	close_heredocs_for_command(t_command *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC && redir->heredoc_fd >= 0)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
}
