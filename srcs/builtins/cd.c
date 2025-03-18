/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:52:53 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/18 16:00:21 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *s, t_data *data)
{
	char	*home_dir;

	if (!s)
	{
		home_dir = ft_getenv(data, "HOME");
		if (chdir(home_dir))
		{
			perror("cd");
			data->exit_status = 1;
		}
	}
	else if (chdir(s))
	{
		perror("cd");
		data->exit_status = 1;
	}
	else
		data->exit_status = 0;
}
