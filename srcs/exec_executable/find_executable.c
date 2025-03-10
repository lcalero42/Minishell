/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:17:56 by ekeisler          #+#    #+#             */
/*   Updated: 2025/03/10 15:17:14 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

char	*find_executable(char *cmd)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[i++])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free(paths);
			return (full_path);
		}
		free(full_path);
	}
	ft_free(paths);
	return (NULL);
}

void	exec_cmd(char *cmd, char **args, char **envp)
{
	char	*executable;
	pid_t	pid;
	int		status;

	pid = fork();
	executable = NULL;
	if (cmd[0] == '/' || cmd[0] == '.')
		executable = cmd;
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		if (executable)
			execve(executable, args, envp);
		handle_unknown_command(cmd);
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
	return ;
}
