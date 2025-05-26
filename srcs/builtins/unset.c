/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 11:15:38 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_env(char **envp, int i);

void	unset(t_command *command, char **envp, t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (command->args[i])
	{
		len = ft_strlen(command->args[i]);
		while (envp[j])
		{
			if (!ft_strncmp(envp[j], command->args[i], len))
			{
				free(envp[j]);
				shift_env(envp, j);
				break ;
			}
			j++;
		}
		i++;
	}
	data->exit_status = 0;
}

static void	shift_env(char **envp, int j)
{
	int	i;

	i = j;
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
}
