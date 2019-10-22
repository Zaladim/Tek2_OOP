/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Timed entity
*/

#ifndef ATIMED_HPP_
#define ATIMED_HPP_

#include "AEntity.hpp"
#include "Timer.hpp"

class ATimed : public AEntity {
	public:
		ATimed(int x, int y, entity e, int delay);
		~ATimed();

		AEntity *update() override;

	protected:
		int _cpt;
	private:
		Timer _t;
};

#endif /* !ATIMED_HPP_ */
