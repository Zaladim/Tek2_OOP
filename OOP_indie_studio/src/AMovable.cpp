/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Moving entity
*/

#include "AMovable.hpp"

AMovable::AMovable()
{
}

AMovable::~AMovable()
{
}

void AMovable::change_dir(direction d)
{
	_dir = d;
}
