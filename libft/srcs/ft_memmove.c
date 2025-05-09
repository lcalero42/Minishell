/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:56:54 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:25 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == 0 && src == 0)
		return (0);
	if (src < dest && src + n >= dest)
	{
		d = dest + n - 1;
		s = (void *) src + n - 1;
		while (n--)
			*d-- = *s--;
	}
	else
	{
		d = dest;
		s = (void *) src;
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}
