/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:10:24 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/14 16:26:43 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var_name(char *parameter, char *envp_var);

void	export(t_data *data)
{
	int		i;
	int		j;
	int		count;

	i = 1;
	j = 0;
	count = 0;
	while (data->commands->args[count])
		count++;
	while (j < count)
	{
		if (!data->envp[i])
		{
			data->envp[i] = ft_strdup(data->commands->args[j]);
			j++;
		}
		else if (check_var_name(data->commands->args[j], data->envp[i]))
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(data->commands->args[j]);
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
