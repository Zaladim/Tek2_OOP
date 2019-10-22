/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** AGame abstract
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "IGame.hpp"

class AGame : public IGame{
	public:
		// === INIT ===
		AGame();
		~AGame();

		// === GETTER ===
		std::vector<std::vector<int>> &getBoard() override;
		int getPos(int x, int y) override;
		int getScore() override;

		// === SETTER ===
		void setBoard(int x, int y) override;
		void setPos(int x, int y, int val) override;


	protected:
		std::vector<std::vector<int>> _board;
		int _score;
	private:
};

#endif /* !AGAME_HPP_ */
