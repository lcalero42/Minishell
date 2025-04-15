/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:28:23 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/15 17:34:26 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_char_to_result(char **rslt, char c);

void	process_quoted_content(char **rslt, char *str, int *i, t_data *data)
{
	char	quote;

	quote = str[0];
	*i = 1;
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '"' && str[*i] == '$')
		{
			handle_env_var(rslt, str, i, data);
			continue ;
		}
		add_char_to_result(rslt, str[*i]);
		(*i)++;
	}
}

void	handle_exit_status(char **rslt, int *i, t_data *data)
{
	char	*exit_status;
	char	*tmp;

	exit_status = ft_itoa(data->exit_status);
	tmp = ft_strjoin(*rslt, exit_status);
	free(*rslt);
	free(exit_status);
	*rslt = tmp;
	(*i)++;
}

void	handle_var_expansion(char **rslt, char *var_name, int *i, t_data *data)
{
	char	*env_var;
	char	*tmp;

	env_var = ft_getenv(data, var_name);
	if (!env_var)
		env_var = ft_strdup("");
	else
		env_var = ft_strdup(env_var);
	tmp = ft_strjoin(*rslt, env_var);
	free(*rslt);
	*rslt = tmp;
	*i += ft_strlen(var_name);
	free(env_var);
}

static void	add_char_to_result(char **rslt, char c)
{
	char	temp[2];
	char	*tmp;

	temp[0] = c;
	temp[1] = '\0';
	tmp = ft_strjoin(*rslt, temp);
	free(*rslt);
	*rslt = tmp;
}
