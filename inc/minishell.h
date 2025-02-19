/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:26:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/02/19 15:55:40 by lcalero          ###   ########.fr       */
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

# define POSSIBLE_NEXT_CMD {"<", ">", "<<", ">>", '|'}
# define NUM_POSSIBLE_CMD 5

typedef struct s_data
{
	char	**cmd;
}	t_data;

void	loop(t_data *data, char **envp);

void	ft_free(char **cmd);

void	pars_input(t_data *data, char *input);

void	print_welcome(void);

void	setup_signal(void);

void	pwd(void);

void	echo(t_data *data);

void	env(char **env);

void	handle_commands(t_data *data, char **envp);

void	cd(char *s);

#endif