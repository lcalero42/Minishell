/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:37:23 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:44 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;
	int		sign;
	int		cpt;

	res = 0;
	i = 0;
	sign = 1;
	cpt = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	while ((nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
		cpt++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && cpt < 2)
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}
