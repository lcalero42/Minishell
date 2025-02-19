/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 16:08:28 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_commands(t_data *data, char **envp)
{
	if (!data->cmd[0])
		return ;
	if (!ft_strncmp("pwd", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 3)
		pwd();
	if (!ft_strncmp("cd", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 2)
		cd(data->cmd[1]);
	if (!ft_strncmp("echo", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 4)
		echo(data);
	if (!ft_strncmp("env", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 3)
		env(envp);
}
