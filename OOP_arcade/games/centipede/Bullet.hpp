/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Bullet
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "Object.hpp"

class Bullet : public Object {
	public:
		Bullet(int x, int y);
		~Bullet();
        bool isActive();
        void setActive(bool activity);

	protected:
	private:
        bool _isActive;
};

#endif /* !BULLET_HPP_ */
