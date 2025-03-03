/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis <luis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:21:31 by luis              #+#    #+#             */
/*   Updated: 2025/03/03 15:47:41 by luis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int is_numeric(char *s);

void    ft_exit(t_data *data)
{
    int exit_code;

    exit_code = 0;
    if (data->cmd[1])
    {
        if (!is_numeric(data->cmd[1]))
            exit_code = 2;
        else
            exit_code = ft_atoi(data->cmd[1]) % 256;
    }
    ft_putstr_fd("exit", 1);
    exit(exit_code);
}

static int is_numeric(char *s)
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
