/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:48:27 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:09 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	long		i;
	char		*res;

	i = ft_strlen(s);
	res = (char *) s;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (res + i);
		i--;
	}
	return ((void *)0);
}
