/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:47:08 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/27 16:35:57 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(int pipe_fd[2], char *delimiter, t_data *data);

int	apply_heredoc(char *delimiter, t_data *data)
{
	int		pipe_fd[2];

	if (!data->can_exec)
		return (-1);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	setup_signal(2);
	read_heredoc(pipe_fd, delimiter, data);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	process_all_heredocs(t_command *cmd_list, t_data *data)
{
	t_command		*current;
	t_redirection	*redir;

	current = cmd_list;
	while (current)
	{
		redir = current->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				redir->heredoc_fd = apply_heredoc(redir->file, data);
			redir = redir->next;
		}
		current = current->next;
	}
}

void	reset_all_heredocs(t_command *cmd_list)
{
	t_command		*current;
	t_redirection	*redir;

	current = cmd_list;
	while (current)
	{
		redir = current->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		current = current->next;
	}
}

static void	read_heredoc(int pipe_fd[2], char *delimiter, t_data *data)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (process_heredoc_line(line, delimiter, data, pipe_fd[1]))
			break ;
	}
	if (g_signals == SIGINT)
		data->can_exec = 0;
}

int	is_quoted(t_data *data)
{
	char	*start;
	char	*word;
	int		i;

	i = 2;
	start = ft_strnstr(data->raw_line, "<<", INT_MAX);
	while (start[i] && ft_isspace(start[i]))
		i++;
	word = extract_word(start + i);
	if (ft_strchr(word, '"') || ft_strchr(word, '\''))
	{
		free(word);
		return (1);
	}
	free(word);
	return (0);
}
