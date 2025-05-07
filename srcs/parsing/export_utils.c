/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:35:01 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/07 16:43:53 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if a variable identifier is valid according to shell rules:
 * - Must start with an alphabetical character or underscore
 * - Cannot consist of only digits
 * - Can only contain alphanumeric characters and underscores
 * 
 * @param identifier The variable identifier to check
 * @return 1 if valid, 0 if invalid
 */
int	is_valid_identifier(char *identifier)
{
	int	i;
	int	all_digits;

	if (!identifier || identifier[0] == '\0')
		return (0);
	if (!(ft_isalpha(identifier[0]) || identifier[0] == '_'))
		return (0);
	all_digits = 1;
	i = 0;
	while (identifier[i])
	{
		if (!(ft_isalnum(identifier[i]) || identifier[i] == '_'))
			return (0);
		if (!(identifier[i] >= '0' && identifier[i] <= '9'))
			all_digits = 0;
		i++;
	}
	if (all_digits)
		return (0);
	return (1);
}

void	handle_valid_arg(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i] && !check_var_name(arg, data->envp[i]))
		i++;
	if (data->envp[i])
		free(data->envp[i]);
	data->envp[i] = ft_strdup(arg);
}

int	process_export_arg(char *arg, t_data *data)
{
	char	**param;
	char	*identifier;

	param = ft_split(arg, '=');
	identifier = param[0];
	if (!is_valid_identifier(identifier))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		ft_free(param);
		data->exit_status = 1;
		return (0);
	}
	handle_valid_arg(arg, data);
	ft_free(param);
	return (1);
}
