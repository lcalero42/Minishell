/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:39:29 by ekeisler          #+#    #+#             */
/*   Updated: 2025/02/18 19:44:24 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pars_input(t_data *data, char *input)
{
	if (!input)
		return ;
	data->cmd = ft_split(input, ' ');
}

void	ft_free(char **cmd)
{
	int	i;
	
	i = 0;
	while (cmd[i])
	{
		if (cmd[i])
			free(cmd[i]);
		i++;
	}
	free(cmd);
}
