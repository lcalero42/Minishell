/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:24:40 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:15 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dest_len)
		return (size + src_len);
	if (size > 0)
	{
		while (src[i] && dest_len + i < size - 1)
		{
			dst[dest_len + i] = src[i];
			i++;
		}
		dst[dest_len + i] = '\0';
	}
	return (dest_len + src_len);
}
