/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Arcade core
*/

#include "Arcade.hpp"

Arcade::Arcade(DLLoader<ILib> libLoader, DLLoader<IGame> gameLoader) : 
	_libLoader(libLoader),
	_gameLoader(gameLoader)
{
	std::string path = "./";
	std::regex graph_lib("^./lib_arcade_.*.so$");
	for (const auto &entry : fs::directory_iterator(path)) {
		if (std::regex_match(entry.path().string(), graph_lib))
			_libs.push_back(entry.path().string());
	}
	path = "./games/";
	std::regex game_lib("^./games/lib_arcade_.*.so$");
	for (const auto &entry : fs::directory_iterator(path)) {
		if (std::regex_match(entry.path().string(), game_lib))
			_games.push_back(entry.path().string());
	}
}

Arcade::~Arcade()
{
}

IGame *Arcade::getGame()
{
	return _running_game;
}

ILib *Arcade::getLib()
{
	return _running_lib;
}

std::vector<std::string> Arcade::getLibList()
{
	return _libs;
}

std::vector<std::string> Arcade::getGameList()
{
	return _games;
}

void Arcade::loadLib(const char *lib)
{
	_running_lib = _libLoader.getInstance(lib);
	_lib_index = std::distance(_libs.begin(), std::find(_libs.begin(), _libs.end(), std::string(lib)));
}

void Arcade::loadGame(const char *game)
{
	_running_game = _gameLoader.getInstance(game);
	_game_index = std::distance(_games.begin(), std::find(_games.begin(), _games.end(), std::string(game)));
}

void Arcade::switch_lib(bool prev)
{
	if (prev) {
		if (_lib_index <= 0)
			_lib_index = _libs.size() - 1;
		else
			_lib_index--;
	} else {
		if (_lib_index >= _libs.size() - 1)
			_lib_index = 0;
		else
			_lib_index++;
	}
	_running_lib = _libLoader.getInstance(_libs[_lib_index].c_str());
}

void Arcade::switch_game(bool prev)
{
	delete _running_game;
	if (prev) {
		if (_game_index <= 0) {
			_game_index = _games.size() - 1;
		} else {
			_game_index--;
		}
	} else {
		if (_game_index >= _games.size() - 1) {
			_game_index = 0;
		} else {
			_game_index++;
		}
	}
	_running_game = _gameLoader.getInstance(_games[_game_index].c_str());
}

int Arcade::run(const char *libFile)
{
	loadLib(libFile);
	loadGame(_games[0].c_str());
	if (!_running_game || !_running_lib) {
		throw std::invalid_argument("Non existing library");
	}
	int command = _running_lib->open(_libs);
	if (command == COMMAND_ERROR)
		return 84;

	while(true) {
		std::string path = "./";
		std::regex graph_lib("^./lib_arcade_.*.so$");
		for (const auto &entry : fs::directory_iterator(path)) {
			if (std::regex_match(entry.path().string(), graph_lib))
				_libs.push_back(entry.path().string());
		}
		path = "./games/";
		std::regex game_lib("^./games/lib_arcade_.*.so$");
		for (const auto &entry : fs::directory_iterator(path)) {
			if (std::regex_match(entry.path().string(), game_lib))
				_games.push_back(entry.path().string());
		}
		if (!_running_game || !_running_lib) {
			throw std::invalid_argument("Non existing library");
		}
		_running_game->update();
		command = _running_lib->run(_libs, _running_game->getBoard(), _running_game->getScore());
		switch (command) {
			case COMMAND_EXIT:
				_running_lib->close();
				_libLoader.close();
				_gameLoader.close();
				return 0;
			case COMMAND_PREV_LIB:
				_running_lib->close();
				_libLoader.close();
				switch_lib(true);
				command = _running_lib->open(_libs);
				break;
			case COMMAND_NEXT_LIB:
				_running_lib->close();
				_libLoader.close();
				switch_lib(false);
				command = _running_lib->open(_libs);
				break;
			case COMMAND_PREV_GAME:
				_gameLoader.close();
				switch_game(true);
				break;
			case COMMAND_NEXT_GAME:
				_gameLoader.close();
				switch_game(false);
				break;
			case COMMAND_UP:
				_running_game->up();
				break;
			case COMMAND_DOWN:
				_running_game->down();
				break;
			case COMMAND_LEFT:
				_running_game->left();
				break;
			case COMMAND_RIGHT:
				_running_game->right();
				break;
			case COMMAND_ACTION:
				_running_game->action();
				break;
			case COMMAND_PLAY:
				delete _running_game;
				_running_game = _gameLoader.getInstance(_games[_game_index].c_str());
				break;
			case COMMAND_ERROR:
				_libLoader.close();
				_gameLoader.close();
				return 84;
		}
	}
	return 0;
}