/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:54:00 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/20 13:15:16 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_parameters(t_command *command, int *i, int *put_endl);
static void	write_output(t_command *command, t_data *data, int i);

void	echo(t_command *command, t_data *data)
{
	int			i;
	int			put_endl;

	i = 0;
	put_endl = 1;
	skip_parameters(command, &i, &put_endl);
	while (command->args[i])
	{
		write_output(command, data, i);
		i++;
	}
	if (put_endl)
		ft_putchar_fd('\n', 1);
	data->exit_status = 0;
}

static void	write_output(t_command *command, t_data *data, int i)
{
	char	*output;
	char	*to_free;

	to_free = NULL;
	if (command->args[i][1] == '?')
	{
		output = ft_itoa(data->exit_status);
		to_free = output;
	}
	else if (command->args[i][0] == '$')
		output = expand_variable(command->args[i] + 1, data);
	else
		output = command->args[i];
	if (output)
		ft_putstr_fd(output, 1);
	if (command->args[i + 1])
		ft_putchar_fd(' ', 1);
	if (to_free)
		free(to_free);
}

static void	skip_parameters(t_command *command, int *i, int *put_endl)
{
	while (command->args[*i] && command->args[*i][0] == '-'
		&& command->args[*i][1] == 'n')
	{
		*put_endl = 0;
		*i += 1;
	}
}
