/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Brick
*/

#ifndef BRICK_HPP_
#define BRICK_HPP_

#include "Object.hpp"

class Brick : public Object {
	public:
		Brick(int x, int y);
		~Brick();

        void gotHit();
        int getHp() const;

	protected:
	private:
        int _hp;
};

#endif /* !BRICK_HPP_ */
