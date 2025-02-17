/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:05:53 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/20 10:19:05 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		cpt++;
		while (s[i] != c && s[i])
			i++;
	}
	return (cpt);
}

static int	ft_len(char const *s, int i, char c)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_strdup_size(const char *s, unsigned int start, char c, int j)
{
	char	*res;
	int		i;
	int		len;

	len = ft_len(s, j, c);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[j] && s[j] != c && i < len)
	{
		res[i] = s[start + i];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

static void	ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (res[i])
			free(res[i]);
		i++;
	}
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		start;
	int		k;

	i = 0;
	k = 0;
	res = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (k < count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		res[k] = ft_strdup_size(s, start, c, i);
		if (res[k] == NULL)
			return (ft_free(res), NULL);
		while (s[i] != c && s[i])
			i++;
		k++;
	}
	res[k] = NULL;
	return (res);
}
