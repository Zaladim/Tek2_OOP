/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Centipede
*/

#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include "../AGame.hpp"
#include "Player.hpp"
#include "Brick.hpp"
#include "Worm.hpp"

#include <stdexcept>

#include <iostream>

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
		Player *_player;
		std::vector<Object*> _objects;
		int _tik;
		bool _gameOver;
	
		// === Internal function ===
		bool check_out_of_bound(Object *obj, int i, int j);
		void updateBullet(Bullet &bullet);
		void createWorm(std::vector<Object*> &_objects);
		bool updateWorm(Worm *worm);
		void hit(int x, int y);
};

#endif /* !CENTIPEDE_HPP_ */
