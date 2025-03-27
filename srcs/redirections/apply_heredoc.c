/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:47:08 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/27 14:31:54 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(char *line, int len, int pipe_fd[2], char *delimiter);

int	apply_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	int		len;

	len = 0;
	line = NULL;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	read_heredoc(line, len, pipe_fd, delimiter);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static void	read_heredoc(char *line, int len, int pipe_fd[2], char *delimiter)
{
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strncmp(line, delimiter, INT_MAX) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
	}
}
