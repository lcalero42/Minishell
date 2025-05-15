/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:10:24 by lcalero           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/13 08:50:30 by ekeisler         ###   ########.fr       */
=======
/*   Updated: 2025/05/08 18:39:36 by lcalero          ###   ########.fr       */
>>>>>>> feature/parsing
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ascii_order(t_data *data);
static char	**init_copy(t_data *data, int count);
static void	swap_env_vars(char **envp, int j);

void	export(t_command *command, t_data *data)
{
	int	j;
	int	count;

	count = 0;
	while (command->args[count])
		count++;
	if (!count)
	{
		print_ascii_order(data);
		data->exit_status = 0;
		return ;
	}
	j = 0;
	while (j < count)
	{
		process_export_arg(command->args[j], data);
		j++;
	}
}

static void	print_ascii_order(t_data *data)
{
	int		i;
	int		j;
	int		count;
	char	**sorted_envp;

	count = 0;
	while (data->envp[count])
		count++;
	sorted_envp = init_copy(data, count);
	if (!sorted_envp)
		return ;
	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
			if (ft_strncmp(sorted_envp[j], sorted_envp[j + 1], INT_MAX) > 0)
				swap_env_vars(sorted_envp, j);
	}
	i = -1;
	while (++i < count)
		print_export_var(sorted_envp[i]);
	ft_free(sorted_envp);
}

static char	**init_copy(t_data *data, int count)
{
	int		i;
	char	**sorted_envp;

	i = 0;
	sorted_envp = malloc(sizeof(char *) * (count + 1));
	if (!sorted_envp)
		return (NULL);
	while (data->envp[i])
	{
		sorted_envp[i] = ft_strdup(data->envp[i]);
		i++;
	}
	sorted_envp[i] = NULL;
	return (sorted_envp);
}

int	check_var_name(char *parameter, char *envp_var)
{
	char	**param;

	param = ft_split(parameter, '=');
	if (!ft_strncmp(param[0], envp_var, ft_strlen(param[0])))
	{
		ft_free(param);
		return (1);
	}
	ft_free(param);
	return (0);
}

static void	swap_env_vars(char **envp, int j)
{
	char	*temp;

	temp = envp[j];
	envp[j] = envp[j + 1];
	envp[j + 1] = temp;
}
