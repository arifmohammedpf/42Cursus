CC		=	gcc
NAME	=	fractol
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm	-rf
SRCS 	=	main.c fractol.c utils_1.c utils_2.c hooks.c
LINUX_MLX_COMMAND = $(CC) $(CFLAGS) $(SRCS) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)
MAC_MLX_COMMAND = $(CC) $(CFLAGS) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx -03 -c $< -o $@

$(NAME): $(SRCS)
	$(MAKE) all -C mlx
	$(LINUX_MLX_COMMAND)
	@echo "Fractol compiled:"
	@echo "1. For Mandlebort => ./$(NAME) 1"
	@echo "2. For Julia => ./$(NAME) -2 2"
	@echo "3. For Tricon => ./$(NAME) 2"

clean:
	$(MAKE) clean -C mlx

fclean: clean
	$(RM) $(NAME)
	$(MAKE) clean -C mlx

re: fclean $(NAME)

.PHONY = all clean fclean re
