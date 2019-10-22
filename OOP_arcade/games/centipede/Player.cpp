/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Centipede player
*/

#include "Player.hpp"

Player::Player(int x, int y) : Object(x, y, PLAYER),
	_bullet(Bullet(-1, -1))
{
}

Player::~Player()
{
}

Bullet &Player::getBullet()
{
	return (_bullet);
}