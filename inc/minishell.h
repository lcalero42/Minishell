/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:26:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/03/26 17:04:47 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES                                    
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

// DEFINES
# define MAX_ARGS 64

// ENUMERATIONS
typedef enum e_token_type
{
	WORD,			// Command and arguments 
	PIPE,			// '|' 
	REDIR_IN,		// '<' 
	REDIR_OUT,		// '>' 
	REDIR_APPEND,	// '>>' 
	HEREDOC,		// '<<' 
	ENV_VAR,		// '$VAR' 
	QUOTE,			// '"' or ''' 
}	t_token_type;

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUT,
	REDIR_HEREDOC,
}	t_redir_type;

// DATA STRUCTURE
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

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
	int					append;
	int					saved_stdin;
	int					saved_stdout;
	t_redirection		*redirections;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	char		*envp[100];
	t_token		*tokens;
	t_command	*commands;
	int			exit_status;
}	t_data;

// TOKENIZER FUNCTION
t_token		*tokenize(char *input, t_data *data);
char		*extract_quoted_string(char *str);
char		*extract_word(char *str);
void		add_token(t_token **tokens, char *value, t_token_type type);
int			ft_isspace(char c);

// PARSER FUNCTION
t_command	*parse_commands(t_token *token_list);
t_command	*init_command(void);
void		add_command(t_command **cmd_list, t_command *new_cmd);
void		add_argument(t_command *cmd, char *arg);
void		add_redirection(t_command *cmd, char *file, t_redir_type type);

// MEMORY MANAGEMENT
void		free_tokens(t_token *tokens);
void		free_commands(t_command *cmd_list);
void		free_redirections(t_redirection *redir);
void		ft_free(char **cmd);
void		ft_free_env(t_data *data);
void		free_all(char *line, t_data *data, t_command *first_cmd);

// ENVIRONMENT FUNCTIONS
int			make_env(t_data *data, char **envp);
char		*expand_variable(char *input, t_data *data);
char		*ft_getenv(t_data *data, char *s);

// BUILTIN COMMANDS
void		pwd(t_data *data);
void		echo(t_command *command, t_data *data);
void		env(char **env, t_data *data);
void		unset(char *var, char **envp, t_data *data);
void		cd(char *s, t_data *data);
void		export(t_command *command, t_data *data);
void		ft_exit(t_command *command, t_data *data);

// EXECUTION FUNCTIONS
void		loop(t_data *data);
void		handle_commands(t_data *data);
void		exec_cmd(t_command *command, t_data *data);
void		handle_unknown_command(char *cmd, t_data *data);
int			apply_redirections(t_command *cmd);
int			apply_heredoc(char *delimiter);
void		reset_fds(t_command *cmd);

// PIPE FUNCTIONS
void		wait_processes(t_data *data, int *status);
void		exec_pipe(t_data *data);
int			check_pipe(t_data *data);
void		setup_fds(t_command *cmd, int fd_in, int *fd);
void		execute_child_process(t_command *cmd, t_data *data,
				int fd_in, int *fd);
int			manage_parent_fd(int fd_in, int *fd, t_command *cmd);
pid_t		create_pipe_and_fork(int *fd, t_command *cmd);
void		exec_programm(t_command *command, t_data *data);
void		find_cmd(t_command *command, t_data *data);
int			is_builtin(t_command *command);

// UTILITY FUNCTIONS
void		print_welcome(void);
void		setup_signal(void);
char		*ft_strncpy(char *destination, const char *source, size_t length);
char		**join_cmd_args(t_command *command);
int			count_args(char **args);

#endif