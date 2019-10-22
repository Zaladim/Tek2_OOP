/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Arcade core
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <vector>
#include <string>
#include <regex>
#include <filesystem>
#include <exception>
#include "DLLoader.hpp"
#include "../lib/ILib.hpp"
#include "../games/IGame.hpp"
#include "../games/centipede/Centipede.hpp"


namespace fs = std::filesystem;

class Arcade {
	public:
		// === INIT ===
		Arcade(DLLoader<ILib> liLloader, DLLoader<IGame> gameLoader);
		~Arcade();

		// === GETTER ===
		IGame *getGame();
		ILib *getLib();
		std::vector<std::string> getLibList();
		std::vector<std::string> getGameList();

		// === LOAD ===
		void loadLib(const char *lib);
		void switch_lib(bool prev);
		void switch_game(bool prev);
		void loadGame(const char *game);

		// === PLAY ===
		int run(const char *libFile);

	protected:
	private:
		DLLoader<ILib> _libLoader;				//Loader of graphical library
		DLLoader<IGame> _gameLoader;
		std::vector<std::string> _libs;		//List of graphicals library
		std::vector<std::string> _games;
		ILib *_running_lib;					//Graphical library actually loaded
		IGame *_running_game;
		int _lib_index;						//Index of graphical library in _libs vector
		int _game_index;
};

#endif /* !ARCADE_HPP_ */
