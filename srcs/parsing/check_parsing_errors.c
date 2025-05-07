/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:21:36 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/07 16:01:39 by ekeisler         ###   ########.fr       */
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
