/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:17:56 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/19 17:12:01 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static char	**join_cmd_args(t_data *data);
static int	count_args(char **args);

void	exec_cmd(t_data *data)
{
	char	*executable;
	pid_t	pid;
	int		status;
	char	**exec_args;

	pid = fork();
	executable = NULL;
	status = 0;
	if (data->commands->command[0] == '/' || data->commands->command[0] == '.')
		executable = data->commands->command;
	exec_args = join_cmd_args(data);
	if (pid < 0)
	{
		perror("fork");
		data->exit_status = 1;
		return ;
	}
	else if (pid == 0)
	{
		if (executable)
			execve(executable, exec_args, data->envp);
		handle_unknown_command(data->commands->command, data);
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
	ft_free(exec_args);
}

static char	**join_cmd_args(t_data *data)
{
	char	**exec_args;
	int		i;

	exec_args = malloc(sizeof(char *) * (count_args(data->commands->args) + 2));
	if (!exec_args)
		return (NULL);
	exec_args[0] = ft_strdup(data->commands->command);
	i = 0;
	while (data->commands->args[i])
	{
		exec_args[i + 1] = ft_strdup(data->commands->args[i]);
		i++;
	}
	exec_args[i + 1] = NULL;
	return (exec_args);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
