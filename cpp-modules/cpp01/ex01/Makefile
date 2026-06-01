NAME = main

SRCS = main.cpp Zombie.cpp zombieHorde.cpp
CXX = c++

CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX)	$(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME) $(OBJS)

re: clean all

.PHONY: all clean fclean re