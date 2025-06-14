/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/27 17:48:44 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_command(t_command *command, t_data *data);
static int	check_reset_redirections(t_command *command, t_data *data);

void	handle_commands(t_data *data)
{
	t_command	*tmp;

	tmp = data->commands;
	process_all_heredocs(tmp, data);
	if (!data->can_exec)
	{
		reset_all_heredocs(tmp);
		return ;
	}
	while (tmp)
	{
		find_command(tmp, data);
		tmp = tmp->next;
	}
}

static void	find_command(t_command *command, t_data *data)
{
	if (!check_reset_redirections(command, data))
		return ;
	if (command->command)
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
			unset(command, data->envp, data);
		else if (!ft_strncmp("export", command->command, INT_MAX))
			export(command, data);
		else if (!ft_strncmp("exit", command->command, INT_MAX))
			ft_exit(command, data);
		else if (command)
			exec_cmd(command, data);
		else
			handle_unknown_command(command->command, data);
	}
	reset_fds(command);
	reset_all_heredocs(data->commands);
}

void	handle_unknown_command(char *cmd, t_data *data)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	data->exit_status = 127;
}

static int	check_reset_redirections(t_command *command, t_data *data)
{
	if (!apply_redirections(command, data))
	{
		reset_fds(command);
		reset_all_heredocs(data->commands);
		return (0);
	}
	return (1);
}
