/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_programm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:35:39 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 11:47:09 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_with_path(char *path, char **exec_args, t_data *data);
static void	clean_and_exit(t_command *command, t_data *data,
				char **exec_args, char *path);
static char	*resolve_executable_path(char *executable, t_data *data,
				t_command *command);

void	exec_programm(t_command *command, t_data *data)
{
	char	*executable;
	char	*path;
	char	**exec_args;

	if (!command->command)
		return ;
	executable = command->command;
	path = resolve_executable_path(executable, data, command);
	exec_args = join_cmd_args(command);
	setup_signal(1);
	if (path)
		execute_with_path(path, exec_args, data);
	else
		execute_with_path(executable, exec_args, data);
	clean_and_exit(command, data, exec_args, path);
}

static void	execute_with_path(char *path, char **exec_args, t_data *data)
{
	execve(path, exec_args, data->envp);
	perror("execve");
}

static void	clean_and_exit(t_command *command, t_data *data,
							char **exec_args, char *path)
{
	reset_fds(command);
	reset_all_heredocs(data->commands);
	if (exec_args)
		ft_free(exec_args);
	free_all(NULL, data, data->commands);
	ft_free_env(data);
	if (path)
		free(path);
	exit(127);
}

static char	*resolve_executable_path(char *executable, t_data *data,
									t_command *command)
{
	char	*path;

	path = NULL;
	if (executable[0] == '/' || executable[0] == '.')
	{
		if (!check_access(executable, data))
		{
			reset_fds(command);
			reset_all_heredocs(data->commands);
			free_all(NULL, data, data->commands);
			ft_free_env(data);
			exit(data->exit_status);
		}
	}
	else
	{
		path = data_get_paths(data->envp, executable);
		if (!path)
		{
			handle_unknown_command(command->command, data);
			clean_and_exit(command, data, NULL, NULL);
		}
	}
	return (path);
}
