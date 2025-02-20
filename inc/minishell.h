/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:26:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/20 23:51:30 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct s_data
{
	char	**cmd;
	char	*envp[100];
}	t_data;

extern char	**environ;

void	loop(t_data *data);

int		make_env(t_data *data, char **envp);

void	ft_free(char **cmd);

void	ft_free_env(t_data *data);

void	pars_input(t_data *data, char *input);

void	print_welcome(void);

void	setup_signal(void);

void	pwd(void);

void	echo(t_data *data);

void	env(char **env);

void	unset(char *var, char **envp);

void	handle_commands(t_data *data);

void	cd(char *s, t_data *data);

char	*expand_variable(char *input, t_data *data);

char *ft_getenv(t_data *data, char *s);

#endif