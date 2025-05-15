/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:14:22 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:06 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*res;
	size_t		j;

	if (!s)
		return (NULL);
	j = 0;
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		res = malloc(ft_strlen(s) - start + 1);
	else
		res = malloc(len * sizeof(char) + 1);
	if (res == NULL)
		return (NULL);
	while (s[start + j] && len > 0)
	{
		res[j] = s[start + j];
		j++;
		len--;
	}
	res[j] = '\0';
	return (res);
}
