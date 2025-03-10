/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:30:29 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/10 18:12:57 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted_string(char *str)
{
	char	*rslt;
	int		i;
	int		size;

	size = 0;
	i = 0;
	if (str[0] == '\'' || str[0] == '"')
		size++;
	while (str[size] != '\'' || str[size] != '"' && str[size])
		size++;
	rslt = malloc(size * sizeof(char));
	if (!rslt)
		return (NULL);
	i = 0;
	if (str[0] == '\'' || str[0] == '"')
		i++;
	while (str[i] != '\'' || str[i] != '"' && str[i])
	{
		rslt[i] = str[i];
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}
