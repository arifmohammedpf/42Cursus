NAME = cub3D

CC = cc

OBJ_DIR = obj

MLX_DIR = mlx_mac

LIBFT_DIR = libft

GNL_DIR = get_next_line

MLX = $(MLX_DIR)/libmlx.a

LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -Iincludes

GNL_SRC = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

ifeq ($(shell uname), Linux)
	MLX_DIR = mlx_linux
	MLX = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif

SRC = src/main.c \
	src/core/exit.c \
	src/core/free.c \
	src/core/game.c \
	src/core/hooks.c \
	src/core/_init.c \
	src/core/_init_mlx.c \
	src/core/_init_utils.c \
	src/engine/ray_vert.c \
	src/engine/ray_horz.c \
	src/engine/ray_utils.c \
	src/engine/ray_casting.c \
	src/engine/player_move.c \
	src/rendering/bg_render.c \
	src/rendering/minimap_init.c \
	src/rendering/pixel_manip.c \
	src/rendering/wall_render.c \
	src/rendering/wall_texture.c \
	src/rendering/minimap_draw.c \
	src/rendering/load_texture.c \
	src/rendering/wall_calculate.c \
	src/rendering/minimap_render.c \
	src/parsing/ascii_art.c \
	src/parsing/parse_cub.c \
	src/parsing/parse_data.c \
	src/parsing/parse_color.c \
	src/parsing/expand_char.c \
	src/parsing/rgb_converter.c \
	src/parsing/parse_map_line.c \
	src/parsing/identifier_lines.c \
	src/parsing/validation/map_validate.c \
	src/parsing/validation/boundary_utils.c \
	src/parsing/validation/config_validate.c \
	src/parsing/validation/texture_validate.c \
	src/parsing/validation/color_validation.c \
	src/parsing/validation/map_char_validate.c \
	src/parsing/validation/boundary_validate.c \

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

GNL_OBJ = $(GNL_SRC:$(GNL_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBS = $(LIBFT) $(MLX) $(MLX_FLAGS)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ) $(GNL_OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GNL_OBJ) $(LIBS)
	@$(call compile_animation)
	@echo "\033[38;5;39m"
	@echo "╔═══════════════════════════════════════════════════════════════════════════════╗"
	@echo "║                                                                               ║"
	@echo "║    ▄████▄   █    ██  ▄▄▄▄    ▓█████ ▓█████▄     ██▀███   ▄▄▄      ▓██   ██▓   ║"
	@echo "║   ▒██▀ ▀█   ██  ▓██▒▓█████▄  ▓█   ▀ ▒██▀ ██▌   ▓██ ▒ ██▒▒████▄     ▒██  ██▒   ║"
	@echo "║   ▒▓█    ▄ ▓██  ▒██░▒██▒ ▄██ ▒███   ░██   █▌   ▓██ ░▄█ ▒▒██  ▀█▄    ▒██ ██░   ║"
	@echo "║   ▒▓▓▄ ▄██▒▓▓█  ░██░▒██░█▀   ▒▓█  ▄ ░▓█▄   ▌   ▒██▀▀█▄  ░██▄▄▄▄██   ░ ▐██▓░   ║"
	@echo "║   ▒ ▓███▀ ░▒▒█████▓ ░▓█  ▀█▓ ░▒████▒░▒████▓    ░██▓ ▒██▒ ▓█   ▓██▒  ░ ██▒▓░   ║"
	@echo "║   ░ ░▒ ▒  ░░▒▓▒ ▒ ▒ ░▒▓███▀▒ ░░ ▒░ ░ ▒▒▓  ▒    ░ ▒▓ ░▒▓░ ▒▒   ▓▒█░   ██▒▒▒    ║"
	@echo "║     ░  ▒   ░░▒░ ░ ░ ▒░▒   ░   ░ ░  ░ ░ ▒  ▒      ░▒ ░ ▒░  ▒   ▒▒ ░ ▓██ ░▒░    ║"
	@echo "║   ░         ░░░ ░ ░  ░    ░     ░    ░ ░  ░      ░░   ░   ░   ▒    ▒ ▒ ░░     ║"
	@echo "║   ░ ░         ░      ░          ░  ░   ░          ░           ░  ░ ░ ░        ║"
	@echo "║   ░                       ░              ░                        ░ ░         ║"
	@echo "║                                                                               ║"
	@echo "║\033[38;5;196m                    ┌─────────────────────────────────────┐                    ║"
	@echo "║                    │       🎯 3D RAYCASTING ENGINE 🎯    │                    ║"
	@echo "║                    └─────────────────────────────────────┘\033[38;5;39m                    ║"
	@echo "║                                                                               ║"
	@echo "║                           \033[38;5;208mby, rradin-m & arimoham\033[38;5;39m                             ║"
	@echo "║                                                                               ║"
	@echo "╚═══════════════════════════════════════════════════════════════════════════════╝"
	@echo "\033[32m"
	@echo "Executable created: $(NAME) | Use valid map file to run it."
	@echo "To run the game, use: ./$(NAME) <path_to_map.cub>"
	@echo "\033[0m"

$(LIBFT):
	@echo "\033[38;5;226m📚 Building libft...\033[0m"
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "\033[38;5;226m🎮 Building MLX...\033[0m"
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "\033[38;5;208m🧹 Cleaning object files...\033[0m"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "\033[38;5;46m✅ Clean complete!\033[0m"

fclean: clean
	@echo "\033[38;5;208m🗑️  Removing executable...\033[0m"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[38;5;46m✅ Full clean complete!\033[0m"

re: fclean all

.PHONY: all clean fclean re start_compile