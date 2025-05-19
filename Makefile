CC = cc
FLAGS = -Wall -Wextra -Werror -Iinc -I.
LDFLAGS = -lreadline -lncurses

include libft.mk

SRCS = srcs/main.c \
	   srcs/parsing/add_token.c \
	   srcs/parsing/tokenize.c \
	   srcs/parsing/extract_quoted_string.c \
	   srcs/parsing/extract_word.c \
	   srcs/parsing/parse_commands.c \
	   srcs/parsing/free_redirections.c \
	   srcs/parsing/check_parsing_errors.c \
	   srcs/parsing/interpreter_word.c \
	   srcs/parsing/check_syntax_errors.c \
	   srcs/parsing/interpreter_word_utils.c \
	   srcs/builtins/cd.c \
	   srcs/builtins/echo.c \
	   srcs/builtins/unset.c \
	   srcs/builtins/env.c \
	   srcs/builtins/pwd.c \
	   srcs/builtins/export.c \
	   srcs/builtins/exit.c \
	   srcs/env/handle_signals.c \
	   srcs/env/handle_env_variables.c \
	   srcs/exec/shell_launching.c \
	   srcs/exec/handle_commands.c \
	   srcs/exec/loop_logic.c \
	   srcs/exec_executable/find_executable.c \
	   srcs/exec_executable/check_access.c \
	   srcs/exec_executable/find_exec_path.c \
	   srcs/redirections/apply_redirections.c \
	   srcs/redirections/apply_heredoc.c \
	   srcs/redirections/reset_fds.c \
	   srcs/pipe_system/exec_pipe.c \
	   srcs/pipe_system/check_pipe.c \
	   srcs/pipe_system/exec_programm.c \
	   srcs/utils/cmd_utils.c \
	   srcs/utils/ft_strncpy.c \
	   srcs/utils/ft_isspace.c \
	   srcs/utils/ft_free.c \
	   srcs/utils/lst_utils.c \
	   srcs/utils/loop_utils.c \
	   srcs/utils/extract_quoted_utils.c \
	   srcs/utils/pipe_system_utils.c \
	   srcs/utils/pipe_exec_utils.c \
	   srcs/utils/export_utils.c \
	   srcs/utils/heredoc_utils.c

HEADER = inc/minishell.h

OBJS_DIR = objects/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(OBJS_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT): $(SRCS_LIBFT) $(LIBFT_HEADER)
	@echo "Building libft..."
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
