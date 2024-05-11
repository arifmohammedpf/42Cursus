CC		=	gcc
NAME	=	fractol
# CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm	-rf
# SRCS 	=	main.c mandelbrot.c julia.c render.c keycontrols.c tricorn.c atof.c
SRCS 	=	main.c fractol.c utils_1.c utils_2.c hooks.c

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx -03 -c $< -o $@

$(NAME): $(SRCS)
	$(MAKE) all -C mlx
	$(CC) $(CFLAGS) $(SRCS) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)
	@echo "Compilation finished: ./$(NAME) [1, 2, <value between -2 & 2> <value between -2 & 2>]"

clean:
	$(MAKE) clean -C mlx

fclean: clean
	$(RM) $(NAME)
	$(MAKE) clean -C mlx

re: fclean $(NAME)

.PHONY = all clean fclean re
