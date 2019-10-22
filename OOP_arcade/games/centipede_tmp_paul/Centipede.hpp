/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Centipede
*/

#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include <utility>
#include <vector>
#include <queue>
#include "../AGame.hpp"

class Centipede : public AGame {
	public:
		Centipede();
		~Centipede();

		// === ACTIONS ===
		void left() override;
		void right() override;
		void up() override;
		void down() override;
		void action() override;

		// === RUN ===
		void update() override;

	protected:
	private:
		int _tik;
	
		enum dir {
			NONE,
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		bool _fire;
		int _prev_shot;
		dir _dir;
		std::pair<int, int> *_player;
		std::pair<int, int> *_shot;
		std::vector<std::vector<std::pair<int, int>*>> _centipedes;

		void addCentipede();
		void moveCentipede(std::vector<std::pair<int, int>*> centipede);
};

#endif /* !CENTIPEDE_HPP_ */
