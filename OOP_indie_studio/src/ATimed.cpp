/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Timed entity
*/

#include "ATimed.hpp"

ATimed::ATimed(int x, int y, entity e, int delay) : 
	AEntity(x, y, e),
	_cpt(delay)
{
}

ATimed::~ATimed()
{
}

AEntity *ATimed::update()
{
	if (_t.getElapsedTime() >= 1000) {
		_cpt --;
		_t.reset();
	}
	if (_cpt <= 0) {
		return nullptr;
	} else {
		return this;
	}
	
}