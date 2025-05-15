/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:26:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/15 17:13:13 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES                                    
# include "../libft/include/libft.h"
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

// GLOBAL VAR
extern volatile sig_atomic_t	g_signals;

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
	int						heredoc_fd;
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
	char				*raw_line;
	char				*envp[100];
	t_token				*tokens;
	t_command			*commands;
	int					exit_status;
	pid_t				*pids;
}	t_data;

// TOKENIZER FUNCTION
t_token		*tokenize(char *input, t_data *data);
char		*extract_quoted_string(char *str, t_data *data);
char		*extract_word(char *str);
void		add_token(t_token **tokens, char *value, t_token_type type);
int			ft_isspace(char c);

// PARSER FUNCTION
t_command	*parse_commands(t_token *token_list);
t_command	*init_command(void);
void		add_command(t_command **cmd_list, t_command *new_cmd);
void		add_argument(t_command *cmd, char *arg);
void		add_redirection(t_command *cmd, char *file, t_redir_type type);
char		*extract_quote_no_expand(char *str);
int			check_parsing_errors(char *s, t_data *data);
void		process_quoted_content(char **rslt, char *str, int *i,
				t_data *data);
void		handle_env_var(char **rslt, char *str, int *i, t_data *data);
void		handle_exit_status(char **rslt, int *i, t_data *data);
void		handle_var_expansion(char **rslt, char *var_name, int *i,
				t_data *data);
char		*interpreter_word(int *i, char *word, t_data *data, int read_quotes);
void		add_char_to_result(char **rslt, char c);
int			check_syntax(t_data *data);

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
int			apply_heredoc(char *delimiter, t_data *data);
void		reset_fds(t_command *cmd);
void		execute_commands(t_data *data);
int			check_access(char *cmd, t_data *data);
char		*data_get_paths(char **envp, char *command);

// PIPE FUNCTIONS
void		wait_processes(t_data *data, pid_t *pids, int num_commands);
void		exec_pipe(t_data *data);
int			check_pipe(t_data *data);
void		execute_child_process(t_command *cmd, t_data *data,
				int fd_in, int *fd);
int			manage_parent_fd(int fd_in, int *fd, t_command *cmd);
pid_t		create_pipe_and_fork(int *fd, t_command *cmd);
void		exec_programm(t_command *command, t_data *data);
void		find_cmd(t_command *command, t_data *data);
int			is_builtin(t_command *command);
int			fork_commands(t_data *data, pid_t *pids, int num_commands);
pid_t		create_child_process(t_command *cmd, t_data *data,
				int fd_in, int *fd);
void		process_all_heredocs(t_command *cmd_list, t_data *data);
void		reset_all_heredocs(t_command *cmd_list);

// UTILITY FUNCTIONS
void		print_welcome(void);
void		setup_signal(int context);
char		*ft_strncpy(char *destination, const char *source, size_t length);
char		**join_cmd_args(t_command *command);
int			count_args(char **args);
int			lst_cmd_len(t_command *cmd);
void		handle_signals_before_input(void);
int			handle_command_result(char *line, int process_result);
void		update_exit_status(t_data *data);
void		execute_and_update(t_data *data);
void		cleanup_iteration(char *line, t_data *data);
char		*get_prompt_line(t_data *data);
int			is_valid_identifier(char *identifier);
void		handle_valid_arg(char *arg, t_data *data);
int			process_export_arg(char *arg, t_data *data);
int			check_var_name(char *parameter, char *envp_var);
void		add_char_to_result(char **rslt, char c);
void		print_export_var(char *env_var);

#endif