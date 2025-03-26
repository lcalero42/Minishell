/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:26:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/26 17:02:03 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_data *data)
{
	t_command	*cmd;
	int			fd[2];
	pid_t		pid;
	int			fd_in;
	int			status;

	cmd = data->commands;
	fd_in = STDIN_FILENO;
	while (cmd)
	{
		pid = create_pipe_and_fork(fd, cmd);
		if (pid == 0)
			execute_child_process(cmd, data, fd_in, fd);
		else if (pid < 0)
		{
			perror("fork");
			return ;
		}
		fd_in = manage_parent_fd(fd_in, fd, cmd);
		cmd = cmd->next;
	}
	wait_processes(data, &status);
}

void	exec_programm(t_command *command, t_data *data)
{
	char	*executable;
	char	**exec_args;

	executable = NULL;
	if ((command->command[0] == '/' || command->command[0] == '.'))
		executable = command->command;
	if (access(command->command, F_OK))
		exit(127);
	exec_args = join_cmd_args(command);
	if (executable)
		execve(executable, exec_args, data->envp);
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
	else
		exit(127);
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
	return (0);
}
