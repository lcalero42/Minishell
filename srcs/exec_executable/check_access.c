/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:34:25 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/02 11:32:08 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	check_dir(char *cmd, t_data *data);
static int	check_char_count(char *cmd, t_data *data);
static int	check_exec(char *cmd, t_data *data);

int	check_access(char *cmd, t_data *data)
{
	struct stat	file_stat;

	if (cmd == NULL || cmd[0] == '\0')
	{
		data->exit_status = 127;
		ft_putstr_fd("minishell: command not found\n", 2);
		return (0);
	}
	if (stat(cmd, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			data->exit_status = 126;
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (0);
		}
	}
	if (!check_dir(cmd, data) || !check_char_count(cmd, data))
		return (0);
	if (!check_exec(cmd, data))
		return (0);
	return (1);
}

int	check_programm_access(char *executable, char *path, t_data *data)
{
	if (executable[0] == '/' || executable[0] == '.')
	{
		if (!check_access(executable, data))
		{
			free(path);
			return (0);
		}
	}
	else
	{
		if (!check_access(path, data))
		{
			free(path);
			return (0);
		}
	}
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
