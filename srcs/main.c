/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/21 00:08:15 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_token tokens;
	(void)av;
	(void)ac;
	setup_signal();
	print_welcome();
	ft_bzero(&data, sizeof(data));
	ft_bzero(&tokens, sizeof(tokens));
	make_env(&data, envp);
	loop(&data, &tokens);
	return (0);
}
