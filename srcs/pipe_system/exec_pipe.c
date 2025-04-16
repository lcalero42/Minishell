/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:26:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/16 17:29:32 by lcalero          ###   ########.fr       */
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
	char	**exec_args;

	executable = NULL;
	if ((command->command[0] == '/' || command->command[0] == '.'))
		executable = command->command;
	if (access(command->command, F_OK))
	{
		reset_fds(command);
		free_all(NULL, data, data->commands);
		ft_free_env(data);
		exit(127);
	}
	exec_args = join_cmd_args(command);
	if (executable)
		execve(executable, exec_args, data->envp);
	reset_fds(command);
	handle_unknown_command(command->command, data);
	ft_free(exec_args);
	free_all(NULL, data, data->commands);
	ft_free_env(data);
	exit(127);
}

void	find_cmd(t_command *command, t_data *data)
{
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
	else if (command->command[0] != '/' && command->command[0] != '.')
	{
		reset_fds(command);
		handle_unknown_command(command->command, data);
		free_all(NULL, data, data->commands);
		ft_free_env(data);
		exit(127);
	}
	reset_fds(command);
}

int	is_builtin(t_command *command)
{
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
