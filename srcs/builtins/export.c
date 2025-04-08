/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:10:24 by lcalero           #+#    #+#             */
/*   Updated: 2025/04/03 15:14:03 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var_name(char *parameter, char *envp_var);
static void	print_ascii_order(t_data *data);
static char	**init_copy(t_data *data, int count);
static void	swap_env_vars(char **envp, int j);

void	export(t_command *command, t_data *data)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (command->args[count])
		count++;
	while (j < count)
	{
		if (!data->envp[i] || check_var_name(command->args[j], data->envp[i]))
		{
			if (data->envp[i])
				free(data->envp[i]);
			data->envp[i] = ft_strdup(command->args[j]);
			j++;
		}
		i++;
	}
	if (!count)
		print_ascii_order(data);
	data->exit_status = 0;
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
		printf("declare -x \"%s\"\n", sorted_envp[i]);
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

static int	check_var_name(char *parameter, char *envp_var)
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
