/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:54:00 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/21 13:54:33 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	echo(t_data *data)
{
	int		i;
	int		put_endl;
	char	*output;

	i = 0;
	put_endl = 1;
	while (data->cmd[++i] && data->cmd[i][0] == '-' && data->cmd[i][1] == 'n')
		put_endl = 0;
	while (data->cmd[i])
	{
		if (data->cmd[i][0] == '$')
			output = expand_variable(data->cmd[i], data);
		else
			output = data->cmd[i];
		if (output)
			ft_putstr_fd(output, 1);
		if (data->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (put_endl)
		ft_putchar_fd('\n', 1);
}
