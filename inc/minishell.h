/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:26:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/12 17:14:31 by lcalero          ###   ########.fr       */
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
# include <limits.h>

typedef enum e_token_type
{
	WORD,			//Command and args
	PIPE,			// '|'
	REDIR_IN,		// '<'
	REDIR_OUT,		// '>'
	REDIR_APPEND,	// '>>'
	HEREDOC,		// '<<'
	ENV_VAR,		// '$VAR'
	QUOTE,			// '"' or '''
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*infile;
	char				*outfile;
	int					append;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	char	**cmd;
	char	*envp[100];
	t_token	*tokens;
}	t_data;

t_token	*tokenize(char *input, t_data *data);

char	*extract_quoted_string(char *str);

char	*extract_word(char *str);

void	add_token(t_token **tokens, char *value, t_token_type type);

int		ft_isspace(char c);

void	loop(t_data *data);

int		make_env(t_data *data, char **envp);

void	ft_free(char **cmd);

void	ft_free_env(t_data *data);

void	print_welcome(void);

void	setup_signal(void);

void	pwd(void);

void	echo(t_data *data);

void	env(char **env);

void	unset(char *var, char **envp);

void	handle_commands(t_data *data);

void	cd(char *s, t_data *data);

void	export(t_data *data);

void	ft_exit(t_data *data);

char	*expand_variable(char *input, t_data *data);

char	*ft_getenv(t_data *data, char *s);

char	*ft_strncpy(char *destination, const char *source, size_t length);

void	exec_cmd(char *cmd, char **args, char **envp);

void	handle_unknown_command(char *cmd);

#endif