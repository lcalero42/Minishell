/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/24 14:50:51 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char *var, char **envp, t_data *data)
{
	int	i;
	int	j;

	if (!var)
		return ;
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], var, ft_strlen(var)))
		{
			free(envp[i]);
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}
