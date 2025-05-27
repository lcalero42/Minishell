/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:27:23 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/27 16:39:25 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_content(int pipe_fd, char *tmp,
				char *res, t_data *data);
static int	check_delimiter(char *tmp, char *delimiter, char *line, char *res);

int	process_heredoc_line(char *line, char *delimiter,
	t_data *data, int pipe_fd)
{
	char	*tmp;
	char	*res;
	int		i;

	tmp = ft_strtrim(line, "\n");
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
	if (!ft_strncmp(tmp, delimiter, INT_MAX))
	{
		line_cleanup(line, tmp, res);
		return (1);
	}
	return (0);
}
