/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:07:46 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/28 10:10:09 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_new_args_array(char **cmd_split, char **existing_args,
				int split_size, int existing_args_count);
static void	fill_new_args_array(char **new_args, char **cmd_split,
				char **existing_args, int split_size);

void	handle_command_with_spaces(t_command *cmd)
{
	char	**cmd_split;
	char	**new_args;
	int		split_size;
	int		existing_args;

	cmd_split = ft_split(cmd->command, ' ');
	split_size = count_args(cmd_split);
	existing_args = count_args(cmd->args);
	free(cmd->command);
	cmd->command = ft_strdup(cmd_split[0]);
	new_args = create_new_args_array(cmd_split, cmd->args,
			split_size, existing_args);
	if (new_args)
	{
		fill_new_args_array(new_args, cmd_split, cmd->args, split_size);
		free(cmd->args);
		cmd->args = new_args;
	}
	ft_free(cmd_split);
}

static char	**create_new_args_array(char **cmd_split, char **existing_args,
									int split_size, int existing_args_count)
{
	char	**new_args;
	int		total_size;

	(void)cmd_split;
	(void)existing_args;
	total_size = existing_args_count + split_size - 1 + 1;
	new_args = malloc(total_size * sizeof(char *));
	return (new_args);
}

static void	fill_new_args_array(char **new_args, char **cmd_split,
								char **existing_args, int split_size)
{
	int	i;
	int	j;
	int	existing_count;

	i = 0;
	j = 1;
	while (j < split_size)
	{
		new_args[i] = ft_strdup(cmd_split[j]);
		i++;
		j++;
	}
	existing_count = count_args(existing_args);
	j = 0;
	while (j < existing_count)
	{
		new_args[i] = existing_args[j];
		i++;
		j++;
	}
	new_args[i] = NULL;
}

int	is_text_token(t_token_type type)
{
	return (type == WORD || type == QUOTE || type == ENV_VAR);
}
