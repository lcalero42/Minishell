/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:26:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/24 17:48:43 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_cmd(t_command *command, t_data *data);

void	exec(t_data *data)
{
	t_command	*cmd;
	int			fd[2];
	pid_t		pid;
	int			fd_in;

	cmd = data->commands;
	fd_in = 0;
	while (cmd)
	{
		if (cmd->next)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (fd_in != 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			if (cmd->next)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
			close(fd[0]);
			apply_redirections(cmd);
			find_cmd(cmd, data);
		}
		if (fd_in != 0)
			close(fd_in);
		if (cmd->next)
		{
			close(fd[1]);
			fd_in = fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
}

int	check_pipe(t_data *data)
{
	t_token *token = data->tokens;

	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

static void	find_cmd(t_command *command, t_data *data)
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
	else if (command->command[0] == '/' || command->command[0] == '.')
		exec_cmd(command, data);
	else
		exit(1);
}

// static int	is_builtin(t_command *command)
// {
// 	if (!ft_strncmp("pwd", command->command, INT_MAX))
// 		return (1);
// 	else if (!ft_strncmp("cd", command->command, INT_MAX))
// 		return (1);
// 	else if (!ft_strncmp("echo", command->command, INT_MAX))
// 		return (1);
// 	else if (!ft_strncmp("env", command->command, INT_MAX))
// 		return (1);
// 	else if (!ft_strncmp("unset", command->command, INT_MAX))
// 		return (1);
// 	else if (!ft_strncmp("export", command->command, INT_MAX))
// 		return (1);
// 	else if (!ft_strncmp("exit", command->command, INT_MAX))
// 		return (1);
// 	return (0);
// }

