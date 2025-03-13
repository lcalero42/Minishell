/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:25:23 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/13 18:54:08 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit(char *line);

void	print_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}

void	loop(t_data *data)
{
	char		*line;
	t_command	*commands;
	while (1)
	{
		line = readline("\e[1;32mMinishell> \e[0m");
		data->tokens = tokenize(line, data);
		data->commands = parse_commands(data->tokens);
		commands = data->commands;
		if (!handle_exit(line))
			break ;
		// printf("\n===== TOKENS =====\n");
		// 	t_token *temp = data->tokens;
		// 	while (temp)
		// 	{
		// 		printf("Token type: %d, Value: '%s'\n", temp->type, temp->value);
		// 		temp = temp->next;
		// 	}
		// printf("=================\n");
		// while (commands)
		// {
		// 	// Print command info
		// 	printf("\n===== COMMAND INFO =====\n");
		// 	printf("Command: '%s'\n", commands->command);
			
		// 	// Print arguments
		// 	printf("Arguments:\n");
		// 	if (commands->args)
		// 	{
		// 		int i = 0;
		// 		while (commands->args[i])
		// 		{
		// 			printf("  arg[%d]: '%s'\n", i, commands->args[i]);
		// 			i++;
		// 		}
		// 	}
		// 	else
		// 		printf("  No arguments\n");
			
		// 	// Print redirections
		// 	printf("Redirections:\n");
		// 	if (commands->redirections)
		// 	{
		// 		t_redirection *redir = commands->redirections;
		// 		int redir_count = 0;
				
		// 		while (redir)
		// 		{
		// 			printf("  [%d] ", redir_count++);
					
		// 			// Print redirection type
		// 			switch (redir->type)
		// 			{
		// 				case REDIR_INPUT:
		// 					printf("Type: INPUT (<)");
		// 					break;
		// 				case REDIR_OUTPUT:
		// 					printf("Type: OUTPUT (>)");
		// 					break;
		// 				case REDIR_APPEND_OUT:
		// 					printf("Type: APPEND (>>)");
		// 					break;
		// 				case REDIR_HEREDOC:
		// 					printf("Type: HEREDOC (<<)");
		// 					break;
		// 				default:
		// 					printf("Type: UNKNOWN");
		// 			}
					
		// 			printf(", File: '%s'\n", redir->file);
		// 			redir = redir->next;
		// 		}
		// 	}
		// 	else
		// 		printf("  No redirections\n");
		// 	printf("=======================\n");
		// 	commands = commands->next;
		// }
		handle_commands(data);
		if (*line)
			add_history(line);
		free(line);
		ft_free(data->cmd);
	}
	free(line);
	ft_free_env(data);
	if (line)
		ft_free(data->cmd);
	rl_clear_history();
}

static int	handle_exit(char *line)
{
	if (!line)
		return (0);
	return (1);
}
