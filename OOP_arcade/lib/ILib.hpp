/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** ILib
*/

#ifndef ILIB_HPP_
#define ILIB_HPP_

#include <cstddef>
#include <vector>
#include <string>
#include "../system/DLLoader.hpp"
#include "../games/IGame.hpp"

#define COMMAND_ERROR 84
#define COMMAND_CONTINUE 0
#define COMMAND_EXIT 42
#define COMMAND_PREV_LIB 1
#define COMMAND_NEXT_LIB 2
#define COMMAND_LEFT 3
#define COMMAND_RIGHT 4
#define COMMAND_UP 5
#define COMMAND_DOWN 6
#define COMMAND_ACTION 7
#define COMMAND_PLAY 41
#define COMMAND_NEXT_GAME 8
#define COMMAND_PREV_GAME 9

class ILib {
	public:
		virtual ~ILib() = default;

		// === START ===
		virtual int open(std::vector<std::string> libs) = 0;
		virtual void close() = 0;
		virtual int run(std::vector<std::string> libs, std::vector<std::vector<int>> board, int score) = 0;

		// === TEXT ===
		virtual void printLib(std::vector<std::string> libs) = 0;
		virtual void printScore(int score) = 0;
		virtual void printName() = 0;

		// === GAME ===
		virtual void displayGame(std::vector<std::vector<int>> board) = 0;
		virtual void displayPause() = 0;
};

#endif /* !ILIB_HPP_ */
