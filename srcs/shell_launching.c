/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_launching.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:38:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/17 17:40:30 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_centered(const char *text);

void	print_welcome()
{
	ft_putstr_fd("\n\n", 1);
	print_centered("███╗   ███╗██╗███╗   ██╗██╗███████╗");
	print_centered("████╗ ████║██║████╗  ██║██║██╔════╝");
	print_centered("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	print_centered("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	print_centered("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	print_centered("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	ft_putstr_fd("\n\n", 1);
}

void	print_centered(const char *text)
{
	int				width;
	int				text_length;
	int				padding;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	width = w.ws_col;
	text_length = strlen(text);
	padding = (width / 2) - text_length;
	if (padding < 0)
		padding = 0;
	ft_putstr_fd("\033[1;34m", 1);
	while (padding-- > 0)
		ft_putstr_fd(" ", 1);
	ft_putstr_fd((char *)text, 1);
	ft_putstr_fd("\033[0m\n", 1);
}

