/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_launching.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:38:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 13:49:39 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_line(const char *text);

void	print_welcome(void)
{
	ft_putstr_fd("\n\n", 1);
	print_line("███╗   ███╗██╗███╗   ██╗██╗███████╗");
	print_line("████╗ ████║██║████╗  ██║██║██╔════╝");
	print_line("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	print_line("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	print_line("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	print_line("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	ft_putstr_fd("\n\n", 1);
}

static void	print_line(const char *text)
{
	ft_putstr_fd("\033[1;34m", 1);
	ft_putstr_fd((char *)text, 1);
	ft_putstr_fd("\033[0m\n", 1);
}
