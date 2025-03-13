/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/13 18:28:27 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_commands(t_data *data)
{
	t_command	*tmp;

	tmp = data->commands;
	while (tmp)
	{
		if (!tmp->command)
			return ;
		else if (!ft_strncmp("pwd", tmp->command, INT_MAX))
			pwd();
		else if (!ft_strncmp("cd", tmp->command, INT_MAX))
			cd(tmp->args[0], data);
		else if (!ft_strncmp("echo", tmp->command, INT_MAX))
			echo(data);
		else if (!ft_strncmp("env", tmp->command, INT_MAX))
			env(data->envp);
		else if (!ft_strncmp("unset", tmp->command, INT_MAX))
			unset(tmp->args[0], data->envp);
		else if (!ft_strncmp("export", tmp->command, INT_MAX))
			export(data);
		else if (!ft_strncmp("exit", tmp->command, INT_MAX))
			ft_exit(data);
		else if ((tmp->command[0] == '/' || tmp->command[0] == '.'))
			exec_cmd(data->cmd[0], data->cmd, data->envp);
		else
			handle_unknown_command(tmp->command);
		tmp = tmp->next;
	}
	return ;
}

void	handle_unknown_command(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	return ;
}
