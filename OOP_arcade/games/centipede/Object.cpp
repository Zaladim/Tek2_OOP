/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Object
*/

#include "Object.hpp"

Object::Object(int x, int y, int value) : 
	_x(x),
	_y(y),
	_value(value)
{
}

Object::~Object()
{
}

// === GETTER ===
int Object::getPosX() const
{
	return _x;
}

int Object::getPosY() const
{
	return _y;
}

int Object::getType() const
{
	return (_value);
}

int Object::isThere(int x, int y)
{
	if (_x == x && _y == y) {
		return (1);
	}
	return (0);
}

// === SETTER ===
void Object::setPos(int x, int y)
{
    _x = x;
    _y = y;
}

void Object::setGround(int value)
{
	_ground = value;
}

// === ACTIONS ===
void Object::move(int hor, int ver)
{
	_x += hor;
	_y += ver;
}

void Object::unsetMap(std::vector<std::vector<int>> &board)
{
	if (_x < board.size() && _y < board[0].size() && _x >= 0 && _y >= 0) {
		board[_x][_y] = _ground;
	}
}

void Object::setMap(std::vector<std::vector<int>> &board)
{
	if (_x < board.size() && _y < board[0].size() && _x >= 0 && _y >= 0) {
		_ground = board[_x][_y];
		board[_x][_y] = _value;
	}
}
