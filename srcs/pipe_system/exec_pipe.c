/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:26:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/25 14:51:33 by lcalero          ###   ########.fr       */
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
	int			status;

	cmd = data->commands;
	fd_in = STDIN_FILENO;
	while (cmd)
	{
		fd[0] = -1;
		fd[1] = -1;
		if (cmd->next)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				return;
			}
		}
		pid = fork();
		if (pid == 0)
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
			if (cmd->next)
			{
				close(fd[0]);
				close(fd[1]);
			}
			apply_redirections(cmd);
			find_cmd(cmd, data);
			free_all(NULL, data, data->commands);
			ft_free_env(data);
			exit(0);
		}
		else if (pid < 0)
		{
			perror("fork");
			return;
		}
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (cmd->next)
		{
			close(fd[1]);
			fd_in = fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0);
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
