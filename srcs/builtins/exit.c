/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:21:31 by luis              #+#    #+#             */
/*   Updated: 2025/03/18 14:07:03 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *s);

void	ft_exit(t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (data->commands->args[0])
	{
		if (!is_numeric(data->commands->args[0]))
			exit_code = 2;
		else
			exit_code = ft_atoi(data->commands->args[0]) % 256;
	}
	ft_putstr_fd("exit\n", 1);
	exit(exit_code);
}

static int	is_numeric(char *s)
{
	if (!s || !*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}
