/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:26:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 19:30:07 by lcalero          ###   ########.fr       */
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
}	t_data;

extern char	**environ;

void	loop(t_data *data);

void	ft_free(char **cmd);

void	pars_input(t_data *data, char *input);

void	print_welcome(void);

void	setup_signal(void);

void	pwd(void);

void	echo(t_data *data);

void	env(char **env);

void	unset(char *var, char **envp);

void	handle_commands(t_data *data);

void	cd(char *s);

char	*expand_variable(char *input);

#endif