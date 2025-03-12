/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/12 15:45:29 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	handle_unknown_command(t_data *data);

void	handle_commands(t_data *data)
{
	if (!data->tokens->value)
		return ;
	else if (!ft_strncmp("pwd", data->tokens->value, INT_MAX))
		pwd();
	else if (!ft_strncmp("cd", data->tokens->value, INT_MAX))
		cd(data->cmd[1], data);
	else if (!ft_strncmp("echo", data->tokens->value, INT_MAX))
		echo(data);
	else if (!ft_strncmp("env", data->tokens->value, INT_MAX))
		env(data->envp);
	else if (!ft_strncmp("unset", data->tokens->value, INT_MAX))
		unset(data->cmd[1], data->envp);
	else if (!ft_strncmp("export", data->tokens->value, INT_MAX))
		export(data);
	else if (!ft_strncmp("exit", data->tokens->value, INT_MAX))
		ft_exit(data);
	else if ((data->cmd[0][0] == '/' || data->cmd[0][0] == '.'))
		exec_cmd(data->cmd[0], data->cmd, data->envp);
	else
		handle_unknown_command(data->cmd[0]);
	return ;
}

void	handle_unknown_command(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	return ;
}
