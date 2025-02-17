/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/17 17:41:32 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*line;
	
	print_welcome();
	while (1)
	{
		line = readline("\e[1;32mMinishell: \e[0m");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
