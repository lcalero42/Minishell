/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/18 17:23:14 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av)
{
	char	*line;
	
	(void)av;
	if (ac != 1)
		return (1);
	setup_signal(SIGINT);
	print_welcome();
	while (1)
	{
		line = readline("\e[1;32mMinishell: \e[0m");
		if (!line)
			break ;
		if (!ft_strncmp("exit", line, 4) || !line)
			break ;
		handle_commands(line);
		if (*line)
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
