/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 13:49:58 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*line;
	t_data	data;

	setup_signal();
	print_welcome();
	ft_bzero(&data, sizeof(data));
	while (1)
	{
		line = readline("\e[1;32mMinishell: \e[0m");
		pars_input(&data, line);
		if (!line)
			break ;
		if (!ft_strncmp("exit", line, 4))
			break ;
		handle_commands(&data);
		if (*line)
			add_history(line);
		free(line);
		ft_free(data.cmd);
	}
	free(line);
	if (line)
		ft_free(data.cmd);
	rl_clear_history();
	return (0);
}
