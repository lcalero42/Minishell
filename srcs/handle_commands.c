/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 13:48:52 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_commands(t_data *data)
{
	if (!data->cmd[0])
		return ;
	if (!ft_strncmp("pwd", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 3)
		pwd();
	if (!ft_strncmp("cd", data->cmd[0], ft_strlen(data->cmd[0]))
		&& ft_strlen(data->cmd[0]) == 2)
		cd(data->cmd[1]);
}
