/*
** EPITECH PROJECT, 2019
** ARCADE 
** File description:
** Centipede player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Bullet.hpp"

class Player : public Object {
	public:
		// === INIT ===
		Player(int x, int y);
		~Player();

		Bullet &getBullet();

	protected:
	private:
		Bullet _bullet;
};

#endif /* !PLAYER_HPP_ */
