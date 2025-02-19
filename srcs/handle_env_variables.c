/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:57:52 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 17:20:59 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_variable(char *input)
{
	int		i;
	char	*var_name;
	char	*output;

	i = 0;
	output = NULL;
	var_name = NULL;
	if (input[0] == '$')
	{
		var_name = ft_strdup(input + 1);
		output = getenv(var_name);
		free(var_name);
	}
	return (output);
}
