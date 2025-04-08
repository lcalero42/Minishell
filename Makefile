CC = cc

FLAGS = -Wall -Wextra -Werror -Iinc -I.
LDFLAGS = -lreadline -lncurses

SRCS = srcs/main.c \
	   libft/ft_putstr_fd.c \
       libft/ft_strlen.c \
	   libft/ft_strncmp.c \
       libft/ft_split.c \
	   libft/ft_bzero.c \
	   libft/ft_putchar_fd.c \
       libft/ft_strlcpy.c \
	   libft/ft_strdup.c \
	   libft/ft_strjoin.c \
	   libft/ft_isdigit.c \
	   libft/ft_atoi.c \
	   libft/ft_itoa.c \
	   libft/get_next_line.c \
	   libft/ft_memcpy.c \
	   libft/ft_strchr.c \
	   libft/ft_calloc.c \
	   libft/ft_isalnum.c \
	   srcs/parsing/ft_strncpy.c \
	   srcs/parsing/add_token.c \
	   srcs/parsing/ft_isspace.c \
	   srcs/parsing/tokenize.c \
	   srcs/parsing/extract_quoted_string.c \
	   srcs/parsing/extract_word.c \
	   srcs/parsing/ft_free.c \
	   srcs/parsing/cmd_utils.c \
	   srcs/parsing/parse_commands.c \
	   srcs/parsing/free_redirections.c \
	   srcs/parsing/lst_utils.c \
	   srcs/parsing/check_parsing_errors.c \
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
	   srcs/redirections/apply_redirections.c \
	   srcs/redirections/apply_heredoc.c \
	   srcs/redirections/reset_fds.c \
	   srcs/pipe_system/exec_pipe.c \
	   srcs/pipe_system/pipe_system_utils.c \
	   srcs/pipe_system/check_pipe.c \
	   srcs/pipe_system/pipe_exec_utils.c

HEADERS = inc/minishell.h

OBJS_DIR = objects/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell

all: $(LIBFT) $(NAME)

$(NAME) : $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(FLAGS) -o $(NAME) $(LIBFT) $(OBJS) $(LDFLAGS)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@echo "Compiling $<...\n"
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_DIR)/libft.h
	@echo "Building libft..."
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	rm -f $(LIBFT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: re fclean clean all