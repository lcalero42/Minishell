/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:52:43 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/18 16:09:03 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	data->exit_status = 0;
}
