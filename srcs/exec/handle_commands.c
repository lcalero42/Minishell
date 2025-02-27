/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/27 11:04:05 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	handle_unknown_command(t_data *data);

void	handle_commands(t_data *data)
{
	if (!data->cmd[0])
		return ;
	else if (!ft_strncmp("pwd", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 3)
		pwd();
	else if (!ft_strncmp("cd", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 2)
		cd(data->cmd[1], data);
	else if (!ft_strncmp("echo", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 4)
		echo(data);
	else if (!ft_strncmp("env", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 3)
		env(data->envp);
	else if (!ft_strncmp("unset", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 5)
		unset(data->cmd[1], data->envp);
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
