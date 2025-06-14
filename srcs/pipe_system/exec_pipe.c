/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:26:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 13:19:05 by lcalero          ###   ########.fr       */
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

void	find_cmd(t_command *command, t_data *data)
{
	if (!command->command)
	{
		reset_all_fds(command);
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
		unset(command, data->envp, data);
	else if (!ft_strncmp("export", command->command, INT_MAX))
		export(command, data);
	else if (!ft_strncmp("exit", command->command, INT_MAX))
		ft_exit(command, data);
	else
	{
		reset_all_fds(command);
		return ;
	}
	reset_all_fds(command);
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
	return (0);
}
