/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:10:28 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/21 00:24:41 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
}

void	cd(char *s, t_data *data)
{
	char	*home_dir;
	char	*old_pwd;

	if (!s)
	{
		home_dir = ft_getenv(data, "HOME");
		if (chdir(home_dir))
			perror("cd");
		return ;
	}
	else if (!strncmp(s, "-", ft_strlen(s)))
	{
		old_pwd = ft_getenv(data, "OLDPWD");
		if (chdir(old_pwd))
			perror("cd");
		return ;
	}
	else if (chdir(s))
	{
		perror("cd");
		return ;
	}
}

void	echo(t_data *data)
{
	int		i;
	int		put_endl;
	char	*output;

	i = 0;
	put_endl = 1;
	while (data->cmd[++i] && data->cmd[i][0] == '-' && data->cmd[i][1] == 'n')
		put_endl = 0;
	while (data->cmd[i])
	{
		if (data->cmd[i][0] == '$')
			output = expand_variable(data->cmd[i], data);
		else
			output = data->cmd[i];
		if (output)
			ft_putstr_fd(output, 1);
		if (data->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (put_endl)
		ft_putchar_fd('\n', 1);
}

void	env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	unset(char *var, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], var, ft_strlen(var))
			&& envp[i][ft_strlen(var)] == '=')
		{
			free(envp[i]);
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}
