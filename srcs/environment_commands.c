/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:10:28 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 13:48:45 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
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
