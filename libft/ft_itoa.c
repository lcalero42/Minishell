/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:41:57 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:37 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	long	num;
	int		cpt;

	cpt = 0;
	num = (long) n;
	if (num < 0)
	{
		cpt++;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		cpt++;
	}
	if (n == 0)
		cpt = 1;
	return (cpt);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	long	num;

	res = malloc(sizeof(char) * count_digits(n) + 1);
	if (res == NULL)
		return (NULL);
	i = count_digits(n);
	num = (long) n;
	if (n < 0)
		num = -num;
	res[i--] = '\0';
	while (num > 0)
	{
		res[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	if (n < 0)
		res[i] = '-';
	if (n == 0)
		res[i] = '0';
	return (res);
}
