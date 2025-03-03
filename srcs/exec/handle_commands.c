/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis <luis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/03 15:36:27 by luis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	handle_unknown_command(t_data *data);

void	handle_commands(t_data *data)
{
	if (!data->cmd[0])
		return ;
	else if (!ft_strncmp("pwd", data->cmd[0], INT_MAX))
		pwd();
	else if (!ft_strncmp("cd", data->cmd[0], INT_MAX))
		cd(data->cmd[1], data);
	else if (!ft_strncmp("echo", data->cmd[0], INT_MAX))
		echo(data);
	else if (!ft_strncmp("env", data->cmd[0], INT_MAX))
		env(data->envp);
	else if (!ft_strncmp("unset", data->cmd[0], INT_MAX))
		unset(data->cmd[1], data->envp);
	else if (!ft_strncmp("export", data->cmd[0], INT_MAX))
		export(data);
	else if (!ft_strncmp("exit", data->cmd[0], INT_MAX))
		ft_exit(data);
	else if ((data->cmd[0][0] == '/' || data->cmd[0][0] == '.'))
		exec_cmd(data->cmd[0], data->cmd, data->envp);
	else
		handle_unknown_command(data->cmd[0]);
	return ;
}

void	handle_unknown_command(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	return ;
}
