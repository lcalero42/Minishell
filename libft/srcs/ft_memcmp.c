/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:45:18 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:27 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*s;

	p = (void *) s1;
	s = (void *) s2;
	while (n > 0)
	{
		if (*p < *s)
			return (*p - *s);
		if (*p > *s)
			return (*p - *s);
		n--;
		p++;
		s++;
	}
	return (0);
}
