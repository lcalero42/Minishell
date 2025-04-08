/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:32:34 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/24 13:51:25 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

static char	*ft_strjoin_and_free(char *s1, char *s2);
static char	*ft_strdup_endl(const char *line);
static void	ft_update(char	*buf);

char	*get_next_line(int fd)
{
	static char		buf[100 + 1];
	int				index;
	char			*line;

	if (fd < 0 || 100 <= 0)
		return (NULL);
	index = 1;
	line = ft_strdup_endl(buf);
	if (!line)
		return (NULL);
	while (index > 0 && !ft_strchr(line, '\n'))
	{
		index = read(fd, buf, 100);
		if (index == -1)
			return (ft_bzero(buf, 100), free(line), NULL);
		buf[index] = '\0';
		line = ft_strjoin_and_free(line, buf);
		if (!line)
			return (NULL);
	}
	if (index == 0 && !line[0])
		return (free(line), NULL);
	ft_update(buf);
	return (line);
}

static char	*ft_strdup_endl(const char *line)
{
	size_t	len;
	char	*str;
	size_t	i;

	len = 0;
	i = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len] == '\n')
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_strjoin_and_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*line;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = 0;
	while (s2[len2] != '\0' && s2[len2] != '\n')
		len2++;
	if (s2[len2] == '\n')
		len2++;
	line = malloc(sizeof(char) * len1 + len2 + 1);
	if (!line)
		return (free(s1), NULL);
	ft_memcpy(line, s1, len1);
	ft_memcpy(line + len1, s2, len2);
	line[len1 + len2] = '\0';
	free(s1);
	return (line);
}

static void	ft_update(char	*buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	while (buf[i])
		buf[j++] = buf[i++];
	buf[j] = '\0';
}
