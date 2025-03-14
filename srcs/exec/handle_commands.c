/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/14 16:47:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_command(t_command *command, t_data *data, int *is_known);
static void	lst_update_command(t_data *data, int is_known);

void	handle_commands(t_data *data)
{
	t_command	*tmp;
	int			is_known_cmd;

	tmp = data->commands;
	is_known_cmd = 1;
	while (tmp)
	{
		find_command(tmp, data, &is_known_cmd);
		tmp = tmp->next;
	}
}

static void	find_command(t_command *command, t_data *data, int *is_known)
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
	else
	{
		*is_known = 0;
		handle_unknown_command(command->command);
	}
	lst_update_command(data, *is_known);
}

void	handle_unknown_command(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	return ;
}

static void	lst_update_command(t_data *data, int is_known)
{
	if (is_known)
		data->commands = data->commands->next;
}
