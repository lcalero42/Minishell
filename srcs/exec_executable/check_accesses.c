/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_accesses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:34:25 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/17 15:40:52 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char *cmd, t_data *data)
{
	if (access(cmd, F_OK))
	{
		data->exit_status = 127;
		perror(cmd);
		return (0);
	}
	if (access(cmd, X_OK))
	{
		data->exit_status = 126;
		perror(cmd);
		return (0);
	}
	return (1);
}
