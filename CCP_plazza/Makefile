##
## EPITECH PROJECT, 2018
## Task01 Day01
## File description:
## Makefile
##

SRC	=	src/main.cpp \
		src/Plazza.cpp \
		src/Pipe.cpp \
		src/Reception.cpp \
		src/Kitchen.cpp \
		src/Timer.cpp \
		src/CookManager.cpp \
		src/Pizza.cpp

OBJ	=	$(SRC:.cpp=.o)

FLAGS =		-std=c++17 -lstdc++fs -pthread

NAME	=	plazza

all:	$(NAME)

$(NAME):
	g++ $(SRC) -o $(NAME) -I./include $(FLAGS)

clean:
	rm -f $(OBJ)
	rm -f tmp/kitchen*

fclean:	clean
	rm -f $(NAME)

re:	fclean all
