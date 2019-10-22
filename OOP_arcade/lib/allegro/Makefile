##
## EPITECH PROJECT, 2018
## ARCADE
## File description:
## Allegro5 Makefile
##

SRC				= 	Allegro.cpp

OBJ_GAME		= 	$(SRC:.cpp=.o)

CPPFLAGS		= 	-Wall -Wextra

LIBFLAGS		=	-shared -fPIC

SDLFLAGS		=   `pkg-config --libs allegro-5 allegro_image-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5`

LIBNAME			= 	lib_arcade_allegro.so

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