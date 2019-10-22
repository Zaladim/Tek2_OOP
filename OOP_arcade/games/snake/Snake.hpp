/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <queue>
#include <utility>
#include <cstdlib>
#include <ctime>
#include "../AGame.hpp"

class Snake : public AGame {
	public:
		Snake();
		~Snake();

		// === ACTIONS ===
		void left() override;
		void right() override;
		void up() override;
		void down() override;
		void action() override;

		// === CLOCK ===
		void update() override;

		// === EAT ===
		void new_pellet();

	protected:
	private:
		enum dir {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		std::queue<std::pair<int, int>> _snake;
		dir _face;
		int _tik;
		bool _gameOver;

};

#endif /* !SNAKE_HPP_ */
