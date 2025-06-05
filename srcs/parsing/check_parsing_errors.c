/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:21:36 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/02 13:02:34 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_closed_quotes(char *s);

int	check_parsing_errors(char *s, t_data *data)
{
	if (!check_closed_quotes(s))
	{
		ft_putstr_fd("Error : quotes not closed\n", 2);
		data->exit_status = 2;
		return (0);
	}
	return (1);
}

static int	check_closed_quotes(char *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (!s[i])
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}
