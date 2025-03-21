/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:52:53 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/21 15:40:30 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(t_data *data);

void	cd(char *s, t_data *data)
{
	char	*home_dir;

	update_oldpwd(data);
	if (!s)
	{
		home_dir = ft_getenv(data, "HOME");
		if (chdir(home_dir))
		{
			perror("cd");
			data->exit_status = 1;
		}
	}
	else if (chdir(s))
	{
		perror("cd");
		data->exit_status = 1;
	}
	else
		data->exit_status = 0;
}

static void	update_oldpwd(t_data *data)
{
	char	cwd[1024];
	char	*res;
	int		i;

	getcwd(cwd, sizeof(cwd));
	res = ft_strdup(cwd);
	if (!res)
		return ;
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp("OLDPWD", data->envp[i], 6))
		{
			free(data->envp[i]);
			data->envp[i] = ft_strjoin("OLDPWD=", res);
			free(res);
		}
		i++;
	}
}
