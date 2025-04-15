/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:06:09 by ekeisler          #+#    #+#             */
/*   Updated: 2025/04/15 19:03:41 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

int	g_signals;

static void	sig_affect(int sig);

void	setup_signal(int in_child)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	if (in_child == 0)
	{
		sa.sa_handler = sig_affect;
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

static void	sig_affect(int sig)
{
	g_signals = sig;
	if (g_signals == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
