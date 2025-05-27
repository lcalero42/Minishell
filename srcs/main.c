/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/27 14:39:46 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	(void)ac;
	print_welcome();
	ft_bzero(&data, sizeof(data));
	data.can_exec = 1;
	make_env(&data, envp);
	loop(&data);
	return (data.exit_status);
}
