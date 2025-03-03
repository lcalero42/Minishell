/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:09:57 by ekeisler          #+#    #+#             */
/*   Updated: 2025/02/24 16:22:15 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strncpy(char *destination, const char *source, size_t length)
{
	size_t	i;

	i = 0;
	while (source[i] && i < length)
	{
		destination[i] = source[i];
		i++;
	}
	while (i < length)
	{
		destination[i] = '\0';
		i++;
	}
	return (destination);
}
