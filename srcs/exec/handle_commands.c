/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/14 15:50:17 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_command(t_command *command, t_data *data);

void	handle_commands(t_data *data)
{
	t_command	*tmp;

	tmp = data->commands;
	while (tmp)
	{
		find_command(tmp, data);
		tmp = tmp->next;
	}
}

static void	find_command(t_command *command, t_data *data)
{
	if (!command->command)
		return ;
	else if (!ft_strncmp("pwd", command->command, INT_MAX))
		pwd();
	else if (!ft_strncmp("cd", command->command, INT_MAX))
		cd(command->args[0], data);
	else if (!ft_strncmp("echo", command->command, INT_MAX))
		echo(data);
	else if (!ft_strncmp("env", command->command, INT_MAX))
		env(data->envp);
	else if (!ft_strncmp("unset", command->command, INT_MAX))
		unset(command->args[0], data->envp);
	else if (!ft_strncmp("export", command->command, INT_MAX))
		export(data);
	else if (!ft_strncmp("exit", command->command, INT_MAX))
		ft_exit(data);
	else if ((command->command[0] == '/' || command->command[0] == '.'))
		exec_cmd(data->cmd[0], data->cmd, data->envp);
	else
		handle_unknown_command(command->command);
}

void	handle_unknown_command(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	return ;
}
