/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/21 14:44:18 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_unknown_command(t_data *data);

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
	else
		handle_unknown_command(data);
}

static void	handle_unknown_command(t_data *data)
{
	ft_putstr_fd(data->cmd[0], 2);
	ft_putstr_fd(": Command not found", 2);
	ft_putchar_fd('\n', 2);
}
