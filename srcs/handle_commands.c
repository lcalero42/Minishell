/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/18 16:48:19 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_commands(char *s)
{
	if (!ft_strncmp("pwd", s, ft_strlen(s)) && s[0])
		pwd();
	if (ft_strnstr(s, "cd", ft_strlen(s)))
		cd(ft_strnstr(s, "cd", ft_strlen(s)) + 3);
}
