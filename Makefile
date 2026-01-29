CC=cc
CFLAGS= -Wall -Wextra -Werror
MLX_FLAGS= -lXext -lX11 -lm -lz
DEBUG_FLAGS=-g3 -fsanitize=address,undefined,leak -D DEBUG

SRCS =	main.c \
		src/parser/parser.c \
		src/parser/parse_light.c \
		src/parser/parse_camera.c \
		src/parser/parser_utils.c \
		src/parser/parse_objects.c \
		src/parser/validate_file.c \
		src/parser/validate_arguments.c \
		src/render/window.c \
		src/vec3d/vec3_arithmetics.c \
		src/vec3d/vec3_products.c \
		src/vec3d/vec3_utils.c \
		src/vec3d/rgb_utils.c \
		src/initializer.c \
		src/intersections/ray_sphere.c \
		src/intersections/ray_plane.c \

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
	@make complete -C $(LIBFT_DIR) > /dev/null
	@echo "$(GREEN)Libft compiled$(RESET)"

$(MLX):
	@make -C $(MLX_PATH) > /dev/null
	@echo "$(GREEN)MLX compiled$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(MLX_PATH) -I $(LIBFT_DIR) -c $< -o $@
	@echo "$(BLUE)Compiling $<...$(RESET)"

$(OBJDIR)/%.debug.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I $(MLX_PATH) -I $(LIBFT_DIR) -c $< -o $@
	@echo "$(CYAN)Compiling $< with debug flags...$(RESET)"
	
debug: $(DEBUG_OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(DEBUG_OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(CYAN)miniRT compiled with debug flags$(RESET)"

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@echo "$(YELLOW)Object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@make clean -C $(MLX_PATH) > /dev/null
	@echo "$(RED)Executable cleaned.$(RESET)"

re: fclean all

.PHONY: all clean fclean re