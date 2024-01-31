CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c ft_lstadd_back.c ft_lstnew.c ft_memcpy.c ft_strlen.c push_utils_2.c \
ft_lstadd_front.c ft_lstprint.c ft_putstr.c ft_substr.c push_moves_1.c push_swap_sort.c \
ft_atoi.c ft_lstlast.c ft_lstsize.c ft_split.c push_moves_2.c push_utils_1.c

OBJ = $(SRC:.c=.o)

NAME = push_swap

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	# rm *.out
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re