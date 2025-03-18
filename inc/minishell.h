/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:26:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/18 14:06:37 by ekeisler         ###   ########.fr       */
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

# define MAX_ARGS 64

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

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUT,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redirection
{
	char					*file;
	t_redir_type			type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*infile;
	char				*outfile;
	int					append;
	t_redirection		*redirections;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	char		*envp[100];
	t_token		*tokens;
	t_command	*commands;
}	t_data;

t_token		*tokenize(char *input, t_data *data);

char		*extract_quoted_string(char *str);

char		*extract_word(char *str);

void		add_token(t_token **tokens, char *value, t_token_type type);

int			ft_isspace(char c);

t_command	*parse_commands(t_token *token_list);

t_command	*init_command(void);

void		add_command(t_command **cmd_list, t_command *new_cmd);

void		add_argument(t_command *cmd, char *arg);

void		add_redirection(t_command *cmd, char *file, t_redir_type type);

void		free_tokens(t_token *tokens);

void		free_commands(t_command *cmd_list);

void		free_redirections(t_redirection *redir);

void		loop(t_data *data);

int			make_env(t_data *data, char **envp);

void		ft_free(char **cmd);

void		ft_free_env(t_data *data);

void		print_welcome(void);

void		setup_signal(void);

void		pwd(void);

void		echo(t_data *data);

void		env(char **env);

void		unset(char *var, char **envp);

void		handle_commands(t_data *data);

void		cd(char *s, t_data *data);

void		export(t_data *data);

void		ft_exit(t_data *data);

char		*expand_variable(char *input, t_data *data);

char		*ft_getenv(t_data *data, char *s);

char		*ft_strncpy(char *destination, const char *source, size_t length);

void		exec_cmd(char *cmd, char **args, char **envp);

void		handle_unknown_command(char *cmd);

#endif