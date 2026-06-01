NAME = megaphone

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS = megaphone.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX)	$(CXXFLAGS) $(OBJS) -o $(NAME)

fclean:
	$(RM) $(NAME) $(OBJS)

re: fclean all

.PHONY: all fclean re