/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:39:29 by ekeisler          #+#    #+#             */
/*   Updated: 2025/02/18 18:53:22 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pars_input(t_data *data, char *input)
{
	data->cmd = ft_split(input, ' ');
	for (int i = 0; data->cmd[i]; i++)
	{
		printf("cmd[%d]: %s\n", i, data->cmd[i]);
	}
}

void	ft_free(char **cmd)
{
	int	i;
	
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
