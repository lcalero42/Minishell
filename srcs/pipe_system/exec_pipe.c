/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:26:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/15 15:29:43 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_data *data)
{
	int		num_commands;

	num_commands = lst_cmd_len(data->commands);
	if (num_commands == 0)
		return ;
	data->pids = ft_calloc(num_commands, sizeof(pid_t));
	if (!data->pids)
	{
		perror("calloc");
		return ;
	}
	if (fork_commands(data, data->pids, num_commands))
		wait_processes(data, data->pids, num_commands);
	free(data->pids);
}

void	exec_programm(t_command *command, t_data *data)
{
	char	*executable;
	char	*path;
	char	**exec_args;

	if (!command->command)
		return ;
	executable = command->command;
	path = NULL;
	if (executable[0] == '/' || executable[0] == '.')
	{
		if (access(executable, F_OK) != 0)
		{
			perror(executable);
			exit(127);
		}
	}
	else
	{
		path = data_get_paths(data->envp, executable);
		if (!path)
		{
			handle_unknown_command(command->command, data);
			exit(127);
		}
	}
	exec_args = join_cmd_args(command);
	setup_signal(1);
	if (path)
		execve(path, exec_args, data->envp);
	else
		execve(executable, exec_args, data->envp);
	perror("execve");
	ft_free(exec_args);
	free(path);
	exit(127);
}

void	find_cmd(t_command *command, t_data *data)
{
	if (!command->command)
	{
		reset_fds(command);
		reset_all_heredocs(data->commands);
		return ;
	}
	if (!ft_strncmp("pwd", command->command, INT_MAX))
		pwd(data);
	else if (!ft_strncmp("cd", command->command, INT_MAX))
		cd(command->args[0], data);
	else if (!ft_strncmp("echo", command->command, INT_MAX))
		echo(command, data);
	else if (!ft_strncmp("env", command->command, INT_MAX))
		env(data->envp, data);
	else if (!ft_strncmp("unset", command->command, INT_MAX))
		unset(command->args[0], data->envp, data);
	else if (!ft_strncmp("export", command->command, INT_MAX))
		export(command, data);
	else if (!ft_strncmp("exit", command->command, INT_MAX))
		ft_exit(command, data);
	else
	{
		reset_fds(command);
		reset_all_heredocs(data->commands);
		exec_programm(command, data);
	}
	reset_fds(command);
	reset_all_heredocs(data->commands);
}

int	is_builtin(t_command *command)
{
	if (!command->command)
		return (1);
	if (!ft_strncmp("pwd", command->command, INT_MAX))
		return (1);
	else if (!ft_strncmp("cd", command->command, INT_MAX))
		return (1);
	else if (!ft_strncmp("echo", command->command, INT_MAX))
		return (1);
	else if (!ft_strncmp("env", command->command, INT_MAX))
		return (1);
	else if (!ft_strncmp("unset", command->command, INT_MAX))
		return (1);
	else if (!ft_strncmp("export", command->command, INT_MAX))
		return (1);
	else if (!ft_strncmp("exit", command->command, INT_MAX))
		return (1);
	else if (command->command[0] != '/' && command->command[0] != '.')
		return (1);
	return (0);
}
