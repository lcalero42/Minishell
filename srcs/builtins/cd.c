/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:52:53 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/10 11:42:28 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd(char *s, t_data *data)
{
	char	*home_dir;

	if (!s)
	{
		home_dir = ft_getenv(data, "HOME");
		if (chdir(home_dir))
			perror("cd");
	}
	else if (chdir(s))
		perror("cd");
}
