/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:15:41 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/24 19:24:01 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_command));
	cmd->args = (char **)malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i <= MAX_ARGS)
	{
		cmd->args[i] = NULL;
		i++;
	}
	return (cmd);
}

void	add_command(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*current;

	if (!cmd_list || !new_cmd)
		return ;
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return ;
	}
	current = *cmd_list;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

void	add_argument(t_command *cmd, char *arg)
{
	int	i;

	if (!cmd && !arg)
		return ;
	i = 0;
	while (cmd->args[i] && i < MAX_ARGS - 1)
		i++;
	if (i >= MAX_ARGS - 1)
		return ;
	cmd->args[i] = ft_strdup(arg);
	cmd->args[i + 1] = NULL;
}

void	add_redirection(t_command *cmd, char *file, t_redir_type type)
{
	t_redirection	*new_redir;
	t_redirection	*last;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return ;
	last = NULL;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
    {
        free(new_redir);
        return;
    }
	new_redir->type = type;
	new_redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

void	free_commands(t_command *cmd_list)
{
	t_command	*current;
	t_command	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		if (current->command)
			free(current->command);
		if (current->args)
			ft_free(current->args);
		if (current->redirections)
			free_redirections(current->redirections);
		free(current);
		current = next;
	}
}
