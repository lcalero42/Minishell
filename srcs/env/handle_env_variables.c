/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis <luis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:57:52 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/03 14:41:42 by luis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	make_env(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
		{
			ft_free_env(data);
			return (0);
		}
		i++;
	}
	data->envp[i] = NULL;
	return (1);
}

char	*ft_getenv(t_data *data, char *s)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], s, ft_strlen(s))
			&& data->envp[i][ft_strlen(s)] == '=')
			return (data->envp[i] + ft_strlen(s) + 1);
		i++;
	}
	return (NULL);
}

char	*expand_variable(char *input, t_data *data)
{
	char	*var_name;
	char	*output;

	output = NULL;
	var_name = NULL;
	if (input[0] == '$')
	{
		var_name = ft_strdup(input + 1);
		output = ft_getenv(data, var_name);
		if (!output)
		{
			free(var_name);
			return (NULL);
		}
		free(var_name);
	}
	return (output);
}

void	ft_free_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		free(data->envp[i]);
		i++;
	}
}
