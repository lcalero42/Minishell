/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:39:31 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/27 16:51:28 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredocs_and_check(t_command *cmd, t_data *data)
{
	process_all_heredocs(cmd, data);
	if (!data->can_exec)
	{
		close_heredocs_for_command(cmd);
		data->can_exec = 1;
		return (0);
	}
	return (1);
}

int	fork_commands(t_data *data, pid_t *pids, int num_commands)
{
	t_command	*cmd;
	int			fd[2];
	int			fd_in;
	int			i;
	pid_t		pid;

	cmd = data->commands;
	if (!handle_heredocs_and_check(cmd, data))
		return (0);
	fd_in = STDIN_FILENO;
	i = 0;
	while (cmd && i < num_commands)
	{
		pid = create_child_process(cmd, data, fd_in, fd);
		if (pid < 0)
			return (perror("fork"), 0);
		pids[i++] = pid;
		close_heredocs_for_command(cmd);
		fd_in = manage_parent_fd(fd_in, fd, cmd);
		cmd = cmd->next;
	}
	return (1);
}

pid_t	create_child_process(t_command *cmd, t_data *data, int fd_in, int *fd)
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

void	close_heredocs_for_command(t_command *cmd)
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
