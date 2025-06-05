/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:27:23 by ekeisler          #+#    #+#             */
/*   Updated: 2025/06/02 16:47:57 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_content(int pipe_fd, char *tmp,
				char *res, t_data *data);
static int	check_delimiter(char *tmp, char *delimiter, char *line, char *res);
static char	*ft_strdup_printable(const char *s);

int	process_heredoc_line(char *line, char *delimiter,
	t_data *data, int pipe_fd)
{
	char	*tmp;
	char	*res;
	int		i;

	tmp = ft_strdup_printable(line);
	if (tmp[ft_strlen(tmp) - 1] == '\n')
		tmp[ft_strlen(tmp) - 1] = '\0';
	res = interpreter_word(&i, tmp, data, 0);
	if (check_delimiter(tmp, delimiter, line, res))
		return (1);
	write_heredoc_content(pipe_fd, tmp, res, data);
	line_cleanup(line, tmp, res);
	return (0);
}

static void	write_heredoc_content(int pipe_fd, char *tmp,
				char *res, t_data *data)
{
	if (!is_quoted(data))
		ft_putstr_fd(res, pipe_fd);
	else
		ft_putstr_fd(tmp, pipe_fd);
	ft_putstr_fd("\n", pipe_fd);
}

static int	check_delimiter(char *tmp, char *delimiter, char *line, char *res)
{
	char	*s;

	s = ft_strtrim(tmp, "\x1C");
	if (!ft_strncmp(s, delimiter, INT_MAX))
	{
		free(s);
		line_cleanup(line, tmp, res);
		return (1);
	}
	free(s);
	return (0);
}

static char	*ft_strdup_printable(const char *s)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] >= 0 && s[i] <= 31 && s[i] != '\n' && s[i] != '\t')
			|| s[i] == 127)
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
