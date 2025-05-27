/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:17:59 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/27 16:21:51 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_interactive_signals(struct sigaction *sa)
{
	restore_ctrl_char_echo();
	sa->sa_handler = sig_handler;
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}

void	setup_command_signals(struct sigaction *sa)
{
	restore_ctrl_char_echo();
	sa->sa_handler = sig_handler_cmd;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

void	setup_heredoc_signals(struct sigaction *sa)
{
	disable_ctrl_char_echo();
	sa->sa_handler = sig_handler_heredoc;
	sigaction(SIGINT, sa, NULL);
	ft_memset(sa, 0, sizeof(*sa));
	sa->sa_handler = SIG_IGN;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGQUIT, sa, NULL);
}
