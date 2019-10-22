##
## EPITECH PROJECT, 2018
## ARCADE
## File description:
## SDL Makefile
##

SRC				= 	NCurses.cpp

OBJ_GAME		= 	$(SRC:.cpp=.o)

CPPFLAGS		= 	-Wall -Wextra

LIBFLAGS		=	-shared -fPIC

LIBNAME			= 	lib_arcade_nCurses.so

NAME			=	NCurses

all:	$(NAME)

$(NAME):
	g++ $(LIBFLAGS) $(SRC) -o $(LIBNAME) -lncurses

clean:
	rm -f *~
	rm -rf *.o
	rm -f *#

fclean: clean
	rm -f $(LIBNAME)*

re:	fclean all

.PHONY: fclean re all clean