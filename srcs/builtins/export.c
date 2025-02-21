/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:10:24 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/21 16:28:46 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_var_name(char *parameter, char *envp_var);

void	export(t_data *data)
{
	int		i;
	int		j;
	int		count;

	i = 1;
	j = 1;
	count = 0;
	while (data->cmd[count])
		count++;
	while (j < count)
	{
		if (!data->envp[i])
		{
			data->envp[i] = ft_strdup(data->cmd[j]);
			j++;
		}
		else if (check_var_name(data->cmd[j], data->envp[i]))
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(data->cmd[j]);
			j++;
		}
		i++;
	}
}

static int	check_var_name(char *parameter, char *envp_var)
{
	char	**param;

	param = ft_split(parameter, '=');
	if (!ft_strncmp(param[0], envp_var, ft_strlen(param[0]))
		&& envp_var[ft_strlen(param[0])] == '=')
	{
		ft_free(param);
		return (1);
	}
	ft_free(param);
	return (0);
}
