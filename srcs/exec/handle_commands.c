/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/12 17:01:45 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	handle_unknown_command(t_data *data);

void	handle_commands(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (!data->tokens->value)
			return ;
		else if (!ft_strncmp("pwd", tmp->value, INT_MAX))
			pwd();
		else if (!ft_strncmp("cd", tmp->value, INT_MAX))
			cd(tmp->value, data);
		else if (!ft_strncmp("echo", tmp->value, INT_MAX))
			echo(data);
		else if (!ft_strncmp("env", tmp->value, INT_MAX))
			env(data->envp);
		else if (!ft_strncmp("unset", tmp->value, INT_MAX))
			unset(tmp->value, data->envp);
		else if (!ft_strncmp("export", tmp->value, INT_MAX))
			export(data);
		else if (!ft_strncmp("exit", tmp->value, INT_MAX))
			ft_exit(data);
		else if ((tmp->value[0] == '/' || tmp->value[0] == '.'))
			exec_cmd(data->cmd[0], data->cmd, data->envp);
		else
			handle_unknown_command(tmp->value);
		tmp = tmp->next;
	}
	return ;
}

void	handle_unknown_command(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	return ;
}
