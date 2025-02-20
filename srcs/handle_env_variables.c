/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:57:52 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/20 15:54:47 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_variable(char *input)
{
	char	*var_name;
	char	*output;

	output = NULL;
	var_name = NULL;
	if (input[0] == '$')
	{
		var_name = ft_strdup(input + 1);
		output = getenv(var_name);
		if (!output)
		{
			free(var_name);
			return (NULL);
		}
		free(var_name);
	}
	return (output);
}
