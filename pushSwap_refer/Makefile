NAME = push_swap
SRCFILES =\
ft_bzero.c\
ft_calloc.c\
ft_lstadd_back.c\
ft_lstadd_front.c\
ft_lstlast.c\
ft_lstnew.c\
ft_lstsize.c\
ft_putstr.c\
ft_split.c\
ft_strlen.c\
ft_substr.c\
ps_atoi.c\
ps_create_stack.c\
ps_freelist.c\
ps_index_stack.c\
ps_instructions.c\
ps_main.c\
ps_print_error_exit.c\
ps_push_swap.c\
ps_sortlst.c\
ps_validate_stack.c
vpath %.c src
OBJPATH = obj/
SRCPATH = src/
SRC = $(addprefix $(SRCPATH), $(SRCFILES))
OBJ = $(patsubst $(SRCPATH)%.c, $(OBJPATH)%.o, $(SRC))
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

.SILENT:

all:	$(OBJPATH) $(NAME)

$(OBJPATH):
	mkdir $(OBJPATH)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	echo "Compilation done successfully!"
	echo "Execute ./push_swap <list of numbers>"

$(OBJPATH)%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJPATH)

fclean: clean
	rm -f $(NAME)

re:		fclean all