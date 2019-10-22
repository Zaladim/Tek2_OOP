##
## EPITECH PROJECT, 2018
## ARCADE
## File description:
## Centipede Makefile
##

SRC				= 	../AGame.cpp 	\
					Snake.cpp

OBJ_GAME		= 	$(SRC:.cpp=.o)

CPPFLAGS		= 	-Wall -Wextra

LIBFLAGS		=	-shared -fPIC

LIBNAME			= 	lib_arcade_

NAME			=	nibbler

all:	$(NAME)

$(NAME):
	g++ $(LIBFLAGS) $(SRC) -o $(LIBNAME)$(NAME).so

clean:
	rm -f *~
	rm -rf *.o
	rm -f *#

fclean: clean
	rm -f $(LIBNAME)*

re:	fclean all

.PHONY: fclean re all clean