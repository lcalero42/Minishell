CC = cc

FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses

SRCS = srcs/main.c libft/ft_putstr_fd.c srcs/shell_launching.c \
		libft/ft_strlen.c libft/ft_strncmp.c srcs/handle_signals.c \
		srcs/environment_commands.c srcs/handle_commands.c srcs/parsing.c \
		libft/ft_split.c
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
	@echo "Compiling $<..."
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