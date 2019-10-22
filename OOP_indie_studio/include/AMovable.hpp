/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Moving entity
*/

#ifndef AMOVABLE_HPP_
#define AMOVABLE_HPP_

#include "AEntity.hpp"

typedef enum direction {
	UP = 2,
	DOWN = 1,
	LEFT = 3,
	RIGHT = 0
} direction_t;

class AMovable {
	public:
		AMovable();
		virtual ~AMovable() = 0;

		void change_dir(direction);
		virtual void move(irr::core::vector3df) = 0;

	protected:
		direction _dir = DOWN;
		bool _move = false;
		float _speed = 30.0f;

	private:
};

#endif /* !AMOVABLE_HPP_ */
