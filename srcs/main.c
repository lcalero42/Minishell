/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/18 19:22:46 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av)
{
	char	*line;
	t_data	data;
	
	(void)av;
	if (ac != 1)
		return (1);
	setup_signal(SIGINT);
	print_welcome();
	while (1)
	{
		line = readline("\e[1;32mMinishell: \e[0m");
		pars_input(&data, line);
		if (!line)
			break ;
		if (!ft_strncmp("exit", line, 4) || !line)
			break ;
		handle_commands(line);
		if (*line)
			add_history(line);
		free(line);
		ft_free(data.cmd);
	}
	ft_free(data.cmd);
	rl_clear_history();
	return (0);
}
