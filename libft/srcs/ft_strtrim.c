/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:18:16 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:08 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_str(const char *s, char a)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	count_chars(const char *str, const char *set)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	cpt;

	i = 0;
	j = ft_strlen(str) - 1;
	cpt = 0;
	if (str[0] == '\0')
		return (0);
	while (is_in_str(set, str[i]) && str[i])
	{
		cpt++;
		i++;
	}
	if (i == ft_strlen(str))
		return (i);
	while (is_in_str(set, str[j]))
	{
		cpt++;
		j--;
	}
	return (cpt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*res;
	size_t			i;
	size_t			j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	res = malloc(ft_strlen(s1) - count_chars(s1, set) * sizeof(char) + 1);
	if (res == NULL)
		return (NULL);
	while (is_in_str(set, s1[i]))
		i++;
	while (j < ft_strlen(s1) - count_chars(s1, set))
	{
		res[j] = s1[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
