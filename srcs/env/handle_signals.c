/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:06:09 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/27 16:24:27 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

volatile sig_atomic_t	g_signals = 0;

void	setup_signal(int context)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	if (context == 0)
		setup_interactive_signals(&sa);
	else if (context == 1)
		setup_command_signals(&sa);
	else if (context == 2)
		setup_heredoc_signals(&sa);
}

void	sig_handler(int sig)
{
	g_signals = sig;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_cmd(int sig)
{
	g_signals = sig;
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sig == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void	sig_handler_heredoc(int sig)
{
	g_signals = sig;
	if (sig == SIGINT)
		write(STDOUT_FILENO, "^C", 3);
}
