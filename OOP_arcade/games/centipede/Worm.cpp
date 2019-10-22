/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Worm
*/

#include "Worm.hpp"

#include <iostream>

Worm::Worm() :
    _lenght(rand()%5 + 10),
    Object(0, 0, ENNEMY),
    _dir(1)
{
    for (unsigned i = 1; i < _lenght; i++) {
        _parts.push_back(Bodypart(0, 0 - i * _dir));
    }
}

Worm::Worm(int x, int y, int dir, int lenght, std::vector<Bodypart> bodyParts) :
    _lenght(lenght),
    Object(x, y, ENNEMY),
    _dir(dir),
    _parts(bodyParts)
{
}

Worm::~Worm()
{
}

int Worm::getDir() const
{
    return (_dir);
}

int Worm::getLenght() const
{
    return (_lenght);
}

void Worm::setDir(int dir)
{
    _dir = dir;
}

int Worm::isThere(int x, int y)
{
    if (_x == x && _y == y)
		return (1);
    for (int it = 0; it < _parts.size(); it++) {
        if (_parts[it].isThere(x, y) > 0)
            return (it + 2);
    }
	return (0);
}

int Worm::cut(int lenght)
{
    int i = _parts.size();
    std::cout << "lenght " << _lenght << " " << _parts.size() << std::endl;

    for (; i > lenght; i--) {
        std::cout << "cut : " << i << std::endl;
        _parts.pop_back();
        _lenght--;
    }
    return i;
}

std::vector<Bodypart> *Worm::getBody(int lenght)
{
    std::vector<Bodypart> *temp_parts = new std::vector<Bodypart>;

    for (unsigned i = (lenght >= 0 ? lenght : 0); i != _parts.size(); i++)
    {
        temp_parts->push_back(_parts[i]);
    }
    return temp_parts;
}

void Worm::swarm(int x, int y, std::vector<std::vector<int>> &board)
{
    int tempx = _x;
    int tempy = _y;
    int xx = _x;
    int yy = _y;

    this->unsetMap(board);
    this->move(x, y);
    this->setMap(board);
    for (Bodypart &i : _parts) {
        i.unsetMap(board);
        xx = i.getPosX();
        yy = i.getPosY();
        i.setPos(tempx, tempy);
        tempx = xx;
        tempy = yy;
        i.setMap(board);
    }
}