##
## EPITECH PROJECT, 2018
## ARCADE
## File description:
## Makefile
##

SRC_LIB			=	lib

SRC_CORE		=	$(CORE)/main.cpp \
					$(CORE)/Arcade.cpp

SRC_GAME		= 	games/AGame.cpp

OBJ_GAME		= 	$(SRC_GAME:.cpp=.o)

LIB				= 	$(SRC_LIB)

CORE			=	system

GAME			= 	games/centipede

CPPFLAGS		= 	-Wall -Wextra

LIBFLAGS		=	-shared -fPIC

COREFLAGS		=	-std=c++17 -lstdc++fs -ldl

LIBNAME			= 	lib_arcade_

NAME			=	arcade

all:	core graphicals games

core:	$(OBJ_GAME)
	g++ $(SRC_CORE) -o $(NAME) $(COREFLAGS)

graphicals:
	make re -C lib/NCurses
	mv lib/NCurses/lib_arcade* .
	make re -C lib/sdl
	mv lib/sdl/lib_arcade* .
	make re -C lib/allegro
	mv lib/allegro/lib_arcade* .

games:
	make re -C games/centipede
	mv games/centipede/lib_arcade* ./games
	make re -C games/snake
	mv games/snake/lib_arcade* ./games

clean:
	rm -f *~
	rm -rf *.o
	rm -f *#
	make clean -C $(GAME)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBNAME)*
	rm -f ./games/$(LIBNAME)*
	make fclean -C $(GAME)

re:	fclean all

.PHONY: fclean re all clean games graphicals core
