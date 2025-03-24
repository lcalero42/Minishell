/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:21:31 by luis              #+#    #+#             */
/*   Updated: 2025/03/21 15:19:36 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *s);

void	ft_exit(t_command *command, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (command->args[0])
	{
		if (!is_numeric(command->args[0]))
			exit_code = 2;
		else
			exit_code = ft_atoi(command->args[0]) % 256;
	}
	free_all(NULL, data, data->commands);
	ft_free_env(data);
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
