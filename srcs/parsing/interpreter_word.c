/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:20:25 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 12:08:24 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_env_var(char *str, t_data *data);

/**
 * Main interpreter function for processing words
 * @return : result of interpretation of the prompt (expands, quotes ...)
 */
char	*interpreter_word(int *i, char *word, t_data *data, int read_quotes)
{
	char	*rslt;

	rslt = ft_strdup("");
	if (!rslt)
		return (NULL);
	if (!process_word_chars(word, data, &rslt, read_quotes))
	{
		free(rslt);
		return (NULL);
	}
	*i += ft_strlen(word) - 1;
	if (!check_wrong_expand(word, rslt))
	{
		free(rslt);
		return (NULL);
	}
	return (rslt);
}

int	check_wrong_expand(char *word, char *rslt)
{
	int		i;
	int		has_expands;

	i = 0;
	has_expands = 0;
	while (word[i])
	{
		if (word[i] == '$')
			has_expands = 1;
		i++;
	}
	if (!rslt[0] && has_expands)
		return (0);
	return (1);
}

/**
 * Handles quoted strings in the interpreter
 * @return: Updated position after processing quotes
 */
size_t	interpreter_quotes(char *word, size_t j, char **rslt, t_data *data)
{
	char	*tmp;
	char	*rslt_temp;
	char	quote_type;

	tmp = extract_quoted_string(word + j, data);
	if (!tmp)
		return (0);
	rslt_temp = *rslt;
	*rslt = ft_strjoin(rslt_temp, tmp);
	free(rslt_temp);
	free(tmp);
	quote_type = word[j];
	j++;
	while (word[j] && word[j] != quote_type)
		j++;
	if (word[j])
		j++;
	return (j);
}

size_t	handle_env_vars(char *word, size_t j, char **rslt, t_data *data)
{
	char	*env_var;
	char	*rslt_temp;

	env_var = extract_env_var(word + j, data);
	if (env_var)
	{
		rslt_temp = *rslt;
		*rslt = ft_strjoin(rslt_temp, env_var);
		free(rslt_temp);
		free(env_var);
		j++;
		if (word[j] == '?')
			j++;
		else
			while (word[j] && (ft_isalnum(word[j]) || word[j] == '_'))
				j++;
	}
	else
		j++;
	return (j);
}

static char	*extract_env_var(char *str, t_data *data)
{
	size_t	i;
	size_t	start;
	char	*var_name;
	char	*var_value;

	i = 1;
	start = i;
	if (!str[i])
		return (ft_strdup("$"));
	if (str[i] == '?')
		return (ft_itoa(data->exit_status));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == start)
		return (NULL);
	var_name = ft_substr(str, start, i - start);
	if (!var_name)
		return (ft_strdup("$"));
	var_value = ft_getenv(data, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}
