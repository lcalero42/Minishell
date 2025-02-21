/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:52:53 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/21 13:54:23 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
