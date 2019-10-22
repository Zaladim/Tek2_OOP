##
## EPITECH PROJECT, 2018
## ARCADE
## File description:
## SDL Makefile
##

SRC				= 	SDL.cpp \
					Texture.cpp \
					Tile.cpp

OBJ_GAME		= 	$(SRC:.cpp=.o)

CPPFLAGS		= 	-Wall -Wextra

LIBFLAGS		=	-shared -fPIC

SDLFLAGS		=   `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -std=c++17 -lstdc++fs -ldl

LIBNAME			= 	lib_arcade_sdl.so

NAME			=	centipede

all:	$(NAME)

$(NAME):
	g++ $(LIBFLAGS) $(SRC) -o $(LIBNAME) $(SDLFLAGS)

clean:
	rm -f *~
	rm -rf *.o
	rm -f *#

fclean: clean
	rm -f $(LIBNAME)*

re:	fclean all

.PHONY: fclean re all clean