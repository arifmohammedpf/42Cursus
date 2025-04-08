CLANG	= cc
FLAGS	= -pthread -Wall -Wextra -Werror 
NAME	= philo
SRCS	= main.c print_error.c init.c utils.c launcher.c philo_eats.c routine.c
OBJS	= $(SRCS:.c=.o)
HEADER	= philo.h

all:	$(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re