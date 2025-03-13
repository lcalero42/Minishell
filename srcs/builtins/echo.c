/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:54:00 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/13 18:43:45 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	int			i;
	int			put_endl;
	char		*output;
	t_command	*tmp;

	i = 0;
	put_endl = 1;
	tmp = data->commands;
	while (tmp->args[i] && tmp->args[i][0] == '-' && tmp->args[i][1] == 'n')
	{
		put_endl = 0;
		i++;
	}
	while (tmp->args[i])
	{
		if (tmp->args[i][0] == '$')
			output = expand_variable(tmp->args[i] + 1, data);
		else
			output = tmp->args[i];
		if (output)
			ft_putstr_fd(output, 1);
		if (tmp->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (put_endl)
		ft_putchar_fd('\n', 1);
}
