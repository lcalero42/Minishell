/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 13:22:23 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*line;

	setup_signal();
	print_welcome();
	while (1)
	{
		line = readline("\e[1;32mMinishell> \e[0m");
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
