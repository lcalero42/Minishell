/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_accesses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:34:25 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/06 17:40:55 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dir(char *cmd, t_data *data);
static int	check_char_count(char *cmd, t_data *data);
static int	check_exec(char *cmd, t_data *data);

int	check_access(char *cmd, t_data *data)
{
	if (cmd == NULL || cmd[0] == '\0')
	{
		data->exit_status = 127;
		ft_putstr_fd("Command not found\n", 2);
		return (0);
	}
	if ((ft_strncmp(cmd, "./", 2) == 0 && strlen(cmd) == 2)
		|| (ft_strncmp(cmd, ".", 1) == 0 && strlen(cmd) == 1)
		|| (ft_strncmp(cmd, "../", 3) == 0 && strlen(cmd) == 3)
		|| (ft_strncmp(cmd, "..", 2) == 0 && strlen(cmd) == 2))
	{
		data->exit_status = 126;
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (0);
	}
	if (!check_dir(cmd, data))
		return (0);
	if (!check_char_count(cmd, data))
		return (0);
	if (!check_exec(cmd, data))
		return (0);
	return (1);
}

static int	check_dir(char *cmd, t_data *data)
{
	int	len_cmd;

	len_cmd = ft_strlen(cmd);
	if (len_cmd > 0 && cmd[len_cmd - 1] == '/')
	{
		data->exit_status = 126;
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (0);
	}
	return (1);
}

static int	check_exec(char *cmd, t_data *data)
{
	if (access(cmd, F_OK))
	{
		data->exit_status = 127;
		perror(cmd);
		return (0);
	}
	if (access(cmd, X_OK))
	{
		data->exit_status = 126;
		perror(cmd);
		return (0);
	}
	return (1);
}

static int	check_char_count(char *cmd, t_data *data)
{
	unsigned long	slash_count;
	unsigned long	dot_count;
	int				i;

	i = 0;
	slash_count = 0;
	dot_count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			slash_count++;
		if (cmd[i] == '.')
			dot_count++;
		i++;
	}
	if ((slash_count > (ft_strlen(cmd) / 2))
		&& (dot_count > (ft_strlen(cmd) / 3)))
	{
		data->exit_status = 127;
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": invalid path\n", 2);
		return (0);
	}
	return (1);
}
