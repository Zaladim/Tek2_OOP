 /*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** nCurses library
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <ncurses.h>
#include <chrono>
#include <thread>
#include "../ALib.hpp"

class NCurses : public ALib {
	public:
		// === INIT ===
		NCurses();
		~NCurses();

		// === GETTER ===
		std::vector<int> &getGameSize();

		// === START ===
		int open(std::vector<std::string> libs) override;
		void close() override;
		int run(std::vector<std::string> libs, std::vector<std::vector<int>> board, int score) override;

		// === TEXT ===
		void printLib(std::vector<std::string> libs) override;
		void printScore(int score) override;
		void printName() override;
		int setName();

		// === GAME ===
		void displayGame(std::vector<std::vector<int>> board) override;
		void displayPause() override;

	protected:
	private:
		WINDOW *_game;
		WINDOW *_lib;
		WINDOW *_score;
		WINDOW *_name;

		int _scoreval;
		std::string _playerName;

		WINDOW *create_newwin(int height, int width, int startY, int startX);
		void destroy_win(WINDOW *local_win);
};

#endif /* !NCURSES_HPP_ */
