/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** IGame Interface
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <vector>
#include <random>

#define WALKABLE 0
#define UNWALKABLE 1
#define PLAYER 2
#define ENNEMY 3
#define SHOT 4
#define EAT 5

class IGame {
	public:
		virtual ~IGame() = default;

		// === GETTER ===
		virtual std::vector<std::vector<int>> &getBoard() = 0;
		virtual int getPos(int x, int y) = 0;
		virtual int getScore() = 0;

		// === SETTER ===
		virtual void setBoard(int x, int y) = 0;
		virtual void setPos(int x, int y, int val) = 0;

		// === ACTIONS ===
		virtual void left() = 0;
		virtual void right() = 0;
		virtual void up() = 0;
		virtual void down() = 0;
		virtual void action() = 0;

		// === CLOCK ===
		virtual void update() = 0;

	protected:
	private:
};

#endif /* !IGAME_HPP_ */
