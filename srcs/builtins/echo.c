/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:54:00 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/14 15:44:13 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	int			i;
	int			put_endl;
	char		*output;

	i = 0;
	put_endl = 1;
	while (data->commands->args[i] && data->commands->args[i][0] == '-'
		&& data->commands->args[i][1] == 'n')
	{
		put_endl = 0;
		i++;
	}
	while (data->commands->args[i])
	{
		if (data->commands->args[i][0] == '$')
			output = expand_variable(data->commands->args[i] + 1, data);
		else
			output = data->commands->args[i];
		if (output)
			ft_putstr_fd(output, 1);
		if (data->commands->args[i++ + 1])
			ft_putchar_fd(' ', 1);
	}
	if (put_endl)
		ft_putchar_fd('\n', 1);
}
