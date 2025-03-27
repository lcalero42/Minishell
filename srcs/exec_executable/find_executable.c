/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:17:56 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/25 16:20:20 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	child_process(t_data *data, char *executable, char **exec_args);
static void	set_exit_status(t_data *data, int status);

void	exec_cmd(t_command *command, t_data *data)
{
	char	*executable;
	pid_t	pid;
	int		status;
	char	**exec_args;

	executable = NULL;
	status = 0;
	if ((command->command[0] == '/' || command->command[0] == '.'))
		executable = command->command;
	if (access(command->command, F_OK))
		return ;
	exec_args = join_cmd_args(command);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		data->exit_status = 1;
		ft_free(exec_args);
		return ;
	}
	if (pid == 0)
		child_process(data, executable, exec_args);
	waitpid(pid, &status, 0);
	set_exit_status(data, status);
	ft_free(exec_args);
}

static void	child_process(t_data *data, char *executable, char **exec_args)
{
	if (executable)
		execve(executable, exec_args, data->envp);
	handle_unknown_command(data->commands->command, data);
	exit(127);
}

static void	set_exit_status(t_data *data, int status)
{
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
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
