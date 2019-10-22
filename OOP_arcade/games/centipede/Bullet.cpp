/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Bullet
*/

#include "Bullet.hpp"

Bullet::Bullet(int x, int y) :
    Object(x, y, SHOT),
    _isActive(false)
{
}

Bullet::~Bullet()
{
}

bool Bullet::isActive()
{
    return (_isActive);
}

void Bullet::setActive(bool activity)
{
    _isActive = activity;
}