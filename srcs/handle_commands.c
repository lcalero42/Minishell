/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 19:29:44 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_unknown_command(t_data *data);

void	handle_commands(t_data *data)
{
	if (!data->cmd[0])
		return ;
	else if (!ft_strncmp("pwd", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 3)
		pwd();
	else if (!ft_strncmp("cd", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 2)
		cd(data->cmd[1]);
	else if (!ft_strncmp("echo", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 4)
		echo(data);
	else if (!ft_strncmp("env", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 3)
		env(environ);
	else if (!ft_strncmp("unset", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 5)
		unset(data->cmd[1], environ);
	else
		handle_unknown_command(data);
}

static void	handle_unknown_command(t_data *data)
{
	ft_putstr_fd(data->cmd[0], 2);
	ft_putstr_fd(": Command not found", 2);
	ft_putchar_fd('\n', 2);
}
