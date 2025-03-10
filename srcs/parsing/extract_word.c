/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:09:33 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/10 18:12:45 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_word(char *str)
{
	int		i;
	int		size;
	char	*rslt;
	
	i = 0;
	size = 0;
	while (ft_isspace(str[size]))
		size++;
	rslt = malloc(sizeof(char) * (size + 1));
	if (!rslt)
		return (NULL);
	while (str[i])
	{
		rslt[i] = rslt[i];
		i++;
	}
	rslt[i] == '\0';
	return (rslt);
}