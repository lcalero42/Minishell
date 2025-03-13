/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:15:41 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/13 17:58:07 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *init_command(void)
{
	t_command *cmd;
	
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	cmd->args = (char **)malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	for (int i = 0; i <= MAX_ARGS; i++)
		cmd->args[i] = NULL;
	
	return (cmd);
}

void	add_command(t_command **cmd_list, t_command *new_cmd)
{
	t_command *current;
	
	if (!cmd_list || !new_cmd)
		return;
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return;
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

void	free_commands(t_command *cmd_list)
{
	t_command *current;
	t_command *next;
	int i;
	
	current = cmd_list;
	while (current)
	{
		next = current->next;
		if (current->command)
			free(current->command);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		free(current);
		current = next;
	}
}
