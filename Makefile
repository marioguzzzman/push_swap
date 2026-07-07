SHELL = /bin/sh
CC = cc
CFLAGS = -Wall -Werror -Wextra -I.
NAME = push_swap.a

SOURCES = ft_printf.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putnbr.c \
	ft_putunsigned.c \
	ft_puthex.c \
	ft_putbase.c \
	ft_putptr.c


OBJECTS = $(SOURCES:.c=.o)

%.o: %.c ft_printf.h
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
