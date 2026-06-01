SRC = main.cpp RPN.cpp

OBJ = $(SRC:.cpp=.o)

CXX = c++

RM = rm -f

CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

NAME = RPN

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
		@$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re