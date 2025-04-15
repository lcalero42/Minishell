/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:30:29 by ekeisler          #+#    #+#             */
/*   Updated: 2025/04/15 18:11:04 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_word_quoted(char *str);

char	*extract_quoted_string(char *str, t_data *data)
{
	char	*rslt;
	int		i;

	if (!str || (str[0] != '\'' && str[0] != '"'))
		return (NULL);
	rslt = ft_strdup("");
	if (!rslt)
		return (NULL);
	process_quoted_content(&rslt, str, &i, data);
	return (rslt);
}

char	*extract_quote_no_expand(char *str)
{
	char	*rslt;
	int		i;
	int		size;
	char	quote;

	if (!str || (str[0] != '\'' && str[0] != '"'))
		return (NULL);
	quote = str[0];
	size = 1;
	while (str[size] && str[size] != quote)
		size++;
	if (str[size] != quote)
		return (NULL);
	rslt = malloc((size) * sizeof(char));
	if (!rslt)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		rslt[i] = str[i + 1];
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}

void	handle_env_var(char **rslt, char *str, int *i, t_data *data)
{
	char	*var_name;
	char	*tmp;

	(*i)++;
	if (!str[*i] || str[*i] == '"' || str[*i] == '\''
		|| !(ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '?'))
	{
		tmp = ft_strjoin(*rslt, "$");
		free(*rslt);
		*rslt = tmp;
		return ;
	}
	if (str[*i] == '?')
	{
		handle_exit_status(rslt, i, data);
		return ;
	}
	var_name = extract_word_quoted(str + *i);
	if (!var_name || var_name[0] == '\0')
	{
		free(var_name);
		return ;
	}
	handle_var_expansion(rslt, var_name, i, data);
	free(var_name);
}

static char	*extract_word_quoted(char *str)
{
	int		i;
	int		j;
	char	*rslt;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	rslt = malloc(sizeof(char) * (i + 1));
	if (!rslt)
		return (NULL);
	j = 0;
	while (j < i)
	{
		rslt[j] = str[j];
		j++;
	}
	rslt[j] = '\0';
	return (rslt);
}
