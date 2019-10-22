/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Brick
*/

#include "Brick.hpp"

Brick::Brick(int x, int y) :
    Object(x, y, EAT),
    _hp(2)
{
    this->setGround(UNWALKABLE);
    std::cout << "create brick" << std::endl;
}

Brick::~Brick()
{
}

void Brick::gotHit()
{
    _hp--;
}

int Brick::getHp() const
{
    return (_hp);
}