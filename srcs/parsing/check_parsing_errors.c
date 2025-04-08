/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:21:36 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/08 17:28:07 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_closed_quotes(char *s);

int	check_parsing_errors(char *s)
{
	if (!check_closed_quotes(s))
	{
		ft_putstr_fd("Error : quotes not closed\n", 2);
		return (0);
	}
	return (1);
}
static int	check_closed_quotes(char *s)
{
	int		i;
	char	quote;
	int		found_quote;

	i = 0;
	found_quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && !found_quote)
		{
			quote = s[i];
			found_quote = 1;
			i++;
			continue ;
		}
		if (found_quote && s[i] == quote)
			return (1);
		i++;
	}
	if (!found_quote)
		return (1);
	return (0);
}
