/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:30:29 by ekeisler          #+#    #+#             */
/*   Updated: 2025/04/08 17:24:05 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_env_var(char **rslt, char *str, int *i, t_data *data);
static char	*extract_word_quoted(char *str);

char	*extract_quoted_string(char *str, t_data *data)
{
	char	*rslt;
	int		i;
	char	quote;
	char	temp[2];
	char	*tmp;

	if (!str || (str[0] != '\'' && str[0] != '"'))
		return (NULL);
	quote = str[0];
	rslt = ft_strdup("");
	if (!rslt)
		return (NULL);
	i = 1;
	while (str[i] && str[i] != quote)
	{
		if (quote == '"' && str[i] == '$')
		{
			handle_env_var(&rslt, str, &i, data);
			continue ;
		}
		temp[0] = str[i];
		temp[1] = '\0';
		tmp = ft_strjoin(rslt, temp);
		free(rslt);
		rslt = tmp;
		i++;
	}
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

static void	handle_env_var(char **rslt, char *str, int *i, t_data *data)
{
	char	*var_name;
	char	*env_var;
	char	*tmp;
	char	*exit_status;

	(*i)++;
	if (!str[*i] || str[*i] == '"' || str[*i] == '\'')
	{
		tmp = ft_strjoin(*rslt, "$");
		free(*rslt);
		*rslt = tmp;
		return ;
	}
	if (str[*i] == '?')
	{
		exit_status = ft_itoa(data->exit_status);
		tmp = ft_strjoin(*rslt, exit_status);
		free(*rslt);
		free(exit_status);
		*rslt = tmp;
		(*i)++;
		return ;
	}
	var_name = extract_word_quoted(str + *i);
	if (!var_name || var_name[0] == '\0')
	{
		free(var_name);
		return ;
	}
	env_var = ft_getenv(data, var_name);
	if (!env_var)
		env_var = ft_strdup("");
	else
		env_var = ft_strdup(env_var);
	tmp = ft_strjoin(*rslt, env_var);
	free(*rslt);
	*rslt = tmp;
	*i += ft_strlen(var_name);
	free(var_name);
	free(env_var);
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
