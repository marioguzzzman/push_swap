SHELL = /bin/sh
CC = cc
CFLAGS = -Wall -Werror -Wextra -I.
NAME = push_swap.a

SOURCES = push_swap.c \
parse_utils.c 

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
	@echo .a archive file created.

clean:
	@rm -f $(OBJECTS)
	@echo All .o object files removed

fclean: clean
	@rm -f $(NAME)
	@echo All .o object files and .a archive files removed

re: fclean all
	@echo All .o files and .a files removed and recreated

.PHONY: all clean fclean re
