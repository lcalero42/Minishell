/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:10:28 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 14:22:08 by lcalero          ###   ########.fr       */
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

void	cd(char *s)
{
	char	*home_dir;
	char	*old_pwd;

	if (!s)
	{
		home_dir = getenv("HOME");
		if (chdir(home_dir))
			perror("cd");
		return ;
	}
	else if (!strncmp(s, "-", ft_strlen(s)))
	{
		old_pwd = getenv("OLDPWD");
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
	int	i;
	int	j;
	int	put_endl;

	i = 1;
	put_endl = 1;
	while (data->cmd[i] && data->cmd[i][0] == '-' && data->cmd[i][1] == 'n')
	{
		j = 1;
		while (data->cmd[i][j] == 'n')
			j++;
		if (data->cmd[i][j] != '\0')
			break ;
		put_endl = 0;
		i++;
	}
	while (data->cmd[i])
	{
		ft_putstr_fd(data->cmd[i], 1);
		if (data->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (put_endl)
		ft_putchar_fd('\n', 1);
}
