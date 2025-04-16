/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_launching.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:38:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/16 16:48:53 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_line(const char *text);
static char	*exit_code_emoji(t_data *data);

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

char	*get_prompt_line(t_data *data)
{
	char	*res;
	char	*emoji;
	
	emoji = exit_code_emoji(data);
	res = ft_strjoin(emoji, " \e[1;32mMinishell> \e[0m");
	return (res);
}

static char	*exit_code_emoji(t_data *data)
{
	if (data->exit_status == 131)
		return ("\xF0\x9F\x92\x80");
	else if (data->exit_status != 0)
		return ("\xE2\x9D\x8C");
	else
		return ("\xE2\x9C\x85");
}

static void	print_line(const char *text)
{
	ft_putstr_fd("\033[1;34m", 1);
	ft_putstr_fd((char *)text, 1);
	ft_putstr_fd("\033[0m\n", 1);
}
