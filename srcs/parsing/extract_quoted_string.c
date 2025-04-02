/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:30:29 by ekeisler          #+#    #+#             */
/*   Updated: 2025/04/02 17:30:53 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_env_var(char **rslt, char *str, int *i, t_data *data);
static char	*extract_word_quoted(char *str);

char *extract_quoted_string(char *str, t_data *data)
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

static void handle_env_var(char **rslt, char *str, int *i, t_data *data)
{
	char 	*var_name;
	char 	*env_var;
	char 	*tmp;
	int 	var_name_len;
	
	(*i)++;
	var_name = extract_word_quoted(str + *i);
	if (!var_name || var_name[0] == '\0')
	{
		free(var_name);
		return ;
	}
	env_var = ft_getenv(data, var_name);
	if (!env_var)
		env_var = ft_strdup("");
	var_name_len = ft_strlen(var_name);
	tmp = ft_strjoin(*rslt, env_var);
	free(*rslt);
	*rslt = tmp;
	free(var_name);
	*i += var_name_len;
}

static char	*extract_word_quoted(char *str)
{
	int		i;
	int		size;
	char	*rslt;

	i = 0;
	size = 0;
	while (!ft_isspace(str[size]) && str[size])
		size++;
	rslt = malloc(sizeof(char) * (size + 1));
	if (!rslt)
		return (NULL);
	while (!ft_isspace(str[i]) && str[i] && str[i] != '"')
	{
		rslt[i] = str[i];
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}
