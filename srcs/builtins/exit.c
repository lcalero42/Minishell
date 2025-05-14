/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:21:31 by luis              #+#    #+#             */
/*   Updated: 2025/05/14 17:19:40 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *s);
static int	strict_atoi(const char *str, int *res);
static void	print_exit_error(char *arg, int type, t_data *data);

void	ft_exit(t_command *cmd, t_data *data)
{
	int	exit_code;
	int	converted;

	ft_putstr_fd("exit\n", 1);
	exit_code = data->exit_status;
	if (cmd->args[0])
	{
		if (!is_numeric(cmd->args[0]) || !strict_atoi(cmd->args[0], &converted))
		{
			print_exit_error(cmd->args[0], 1, data);
			exit(2);
		}
		else if (cmd->args[1])
			return (print_exit_error(NULL, 2, data));
		else
			exit_code = converted % 256;
	}
	reset_fds(cmd);
	free_all(NULL, data, data->commands);
	ft_free_env(data);
	exit(exit_code);
}

static void	print_exit_error(char *arg, int type, t_data *data)
{
	if (type == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->exit_status = 2;
	}
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_status = 1;
	}
}

static int	is_numeric(char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

static int	strict_atoi(const char *str, int *res)
{
	long long	val;
	int			sign;

	val = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
		else
			sign = 1;
	}
	while (*str)
	{
		val = val * 10 + (*str - '0');
		if ((val * sign) > INT_MAX || (val * sign) < INT_MIN)
			return (0);
		str++;
	}
	*res = (int)(val * sign);
	return (1);
}
