CC	= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ft_printf.c ft_print_functions.c
OBJS	= $(SRCS:.c=.o)
NAME	= libftprintf.a
RM	= rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@$(RM) $(OBJS)
			@echo "clean success"

fclean:		clean
			@$(RM) *.out
			@$(RM) $(NAME)
			@echo "full clean"

re:			fclean all

.PHONY:		all clean fclean re