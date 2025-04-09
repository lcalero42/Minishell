/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_system_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:55:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/09 16:27:25 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_fds(t_command *cmd, int fd_in, int *fd);

void	wait_processes(t_data *data, pid_t *pids, int num_commands)
{
	int	i;
	int	child_status;

	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &child_status, 0);
		if (i == num_commands - 1)
		{
			if (WIFEXITED(child_status))
				data->exit_status = WEXITSTATUS(child_status);
			else if (WIFSIGNALED(child_status))
				data->exit_status = 128 + WTERMSIG(child_status);
		}
		i++;
	}
}

void	execute_child_process(t_command *cmd, t_data *data,
									int fd_in, int *fd)
{
	setup_fds(cmd, fd_in, fd);
	if (cmd->next)
	{
		close(fd[0]);
		close(fd[1]);
	}
	apply_redirections(cmd);
	if (is_builtin(cmd))
	{
		find_cmd(cmd, data);
		free_all(NULL, data, data->commands);
		ft_free_env(data);
		exit(data->exit_status);
	}
	else
		exec_programm(cmd, data);
	free_all(NULL, data, data->commands);
	ft_free_env(data);
	exit(0);
}

int	manage_parent_fd(int fd_in, int *fd, t_command *cmd)
{
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (cmd->next)
	{
		close(fd[1]);
		return (fd[0]);
	}
	return (STDIN_FILENO);
}

pid_t	create_pipe_and_fork(int *fd, t_command *cmd)
{
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;
	if (cmd->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	pid = fork();
	return (pid);
}

static void	setup_fds(t_command *cmd, int fd_in, int *fd)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			exit(1);
		}
		close(fd_in);
	}
	if (cmd->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			exit(1);
		}
	}
}
