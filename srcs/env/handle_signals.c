/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:06:09 by ekeisler          #+#    #+#             */
/*   Updated: 2025/04/14 18:32:22 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

static void	sig_handler(int sig);

void	setup_signal(int is_child, t_data *data)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	if (is_child == 0)
	{
		sa.sa_handler = sig_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
	}
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
}
