/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Main
*/

#include "Arcade.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
		return 84;
	DLLoader<ILib> libLoader;
	DLLoader<IGame> gameLoader;

	Arcade arcade(libLoader, gameLoader);
	try {
		return arcade.run(argv[1]);
	} catch (const std::exception &e) {
		return 84;
	}
	return 0;
}

