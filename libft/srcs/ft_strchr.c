/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:32:55 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:18 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		firstindex;
	char	*b;

	b = (char *) s;
	i = ft_strlen(s);
	firstindex = -1;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			firstindex = i;
		}
		i--;
	}
	if (firstindex == -1)
		return ((void *)0);
	return (b + firstindex);
}
