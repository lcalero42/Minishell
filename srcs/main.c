/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/14 18:31:03 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	(void)ac;
	setup_signal(0, &data);
	print_welcome();
	ft_bzero(&data, sizeof(data));
	make_env(&data, envp);
	loop(&data);
	return (0);
}
