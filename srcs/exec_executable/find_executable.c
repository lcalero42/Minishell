/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:17:56 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/15 16:02:07 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_data *data, char *executable,
				char **exec_args, char *path);
static void	set_exit_status(t_data *data, int status);

void	exec_cmd(t_command *command, t_data *data)
{
	char	*executable;
	pid_t	pid;
	int		status;
	char	**exec_args;
	char	*path;

	executable = command->command;
	path = data_get_paths(data->envp, executable);
	if (executable[0] == '/' || executable[0] == '.')
	{
		if (!check_access(executable, data))
			return ;
	}
	else
	{
		if (!check_access(path, data))
			return ;
	}
	exec_args = join_cmd_args(command);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		data->exit_status = 1;
		free(path);
		ft_free(exec_args);
		return ;
	}
	if (pid == 0)
		child_process(data, executable, exec_args, path);
	waitpid(pid, &status, 0);
	set_exit_status(data, status);
	free(path);
	ft_free(exec_args);
}

static void	child_process(t_data *data, char *executable,
	char **exec_args, char *path)
{
	setup_signal(1);
	if (path)
	{
		if (execve(path, exec_args, data->envp) == -1)
			perror("execve with path");
	}
	else if (executable)
	{
		if (execve(executable, exec_args, data->envp) == -1)
			perror("execve with executable");
	}
	handle_unknown_command(data->commands->command, data);
	free(path);
	ft_free(exec_args);
	exit(127);
}

static void	set_exit_status(t_data *data, int status)
{
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_signals = WTERMSIG(status);
		data->exit_status = 128 + g_signals;
		if (g_signals == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 1);
		else if (g_signals == SIGINT)
			data->exit_status = 130;
	}
	else
		data->exit_status = 0;
	setup_signal(0);
}

char	**join_cmd_args(t_command *command)
{
	char	**exec_args;
	int		i;

	exec_args = malloc(sizeof(char *) * (count_args(command->args) + 2));
	if (!exec_args)
		return (NULL);
	exec_args[0] = ft_strdup(command->command);
	i = 0;
	while (command->args[i])
	{
		exec_args[i + 1] = ft_strdup(command->args[i]);
		i++;
	}
	exec_args[i + 1] = NULL;
	return (exec_args);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
