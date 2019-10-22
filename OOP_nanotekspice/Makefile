##
## EPITECH PROJECT, 2018
## NANO TEK SPICE
## File description:
## Makefile
##

SRC				=	${wildcard *.cpp}

CPPFLAGS		= 	-Wall -Wextra -lncurses

NAME			=	nanotekspice

all:	$(NAME)

$(NAME):
	g++ $(SRC) -o $(NAME)

clean:
	rm -f *~
	rm -f *.o
	rm -f *#

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: fclean re all clean
