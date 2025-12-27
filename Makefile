CC=cc
CFLAGS= -Wall -Wextra -Werror
MLX_FLAGS= -lXext -lX11 -lm -lz
DEBUG_FLAGS=-g3 -fsanitize=address,undefined,leak -D DEBUG

SRCS =	main.c

# Object files
OBJDIR=obj
OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DEBUG_OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.c=.debug.o))

LIBFT= libft/libft.a
LIBFT_DIR= libft

MLX_PATH= ./mlx
MLX= $(MLX_PATH)/libmlx.a

NAME= miniRT

# Colors
GREEN=\033[0;32m
BLUE=\033[0;34m
YELLOW=\033[0;33m
RED=\033[0;31m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)miniRT compiled$(RESET)"

$(LIBFT):
	@make complete -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled$(RESET)"

$(MLX):
	@make -C $(MLX_PATH)
	@echo "$(GREEN)MLX compiled$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(MLX_PATH) -I $(LIBFT_DIR) -c $< -o $@
	@echo "$(BLUE)Compiling $<...$(RESET)"

$(OBJDIR)/%.debug.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I $(MLX_PATH) -I $(LIBFT_DIR) -c $< -o $@
	@echo "$(CYAN)Compiling $< with debug flags...$(RESET)"
	
debug: $(DEBUG_OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(DEBUG_OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(CYAN)miniRT compiled with debug flags$(RESET)"

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_PATH)

re: fclean all

.PHONY: all clean fclean re