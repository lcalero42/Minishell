/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:30:29 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/12 15:13:07 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted_string(char *str)
{
	char	*rslt;
	int		i;
	int		size;
	char	quote;

	if (!str || (str[0] != '\'' && str[0] != '"'))
		return (NULL);
	quote = str[0];
	size = 1;
	while (str[size] && str[size] != quote)
		size++;
	if (str[size] != quote)
		return (NULL);
	rslt = malloc((size) * sizeof(char));
	if (!rslt)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		rslt[i] = str[i + 1];
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}
