/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:40:21 by ekeisler          #+#    #+#             */
/*   Updated: 2025/05/14 17:21:46 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*data_find_path(char **paths, char *command);

char	*data_get_paths(char **envp, char *command)
{
	int		i;
	char	*env_path;
	char	**paths;
	char	*res;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	paths = ft_split(env_path, ':');
	res = data_find_path(paths, command);
	ft_free(paths);
	return (res);
}

static char	*data_find_path(char **paths, char *command)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		res = ft_strjoin(tmp, command);
		free(tmp);
		if (!res)
			return (NULL);
		if (!access(res, F_OK))
			return (res);
		free(res);
		i++;
	}
	return (ft_strdup(res));
}
