/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Mobs
*/

#include "Monster.hpp"

Monster::Monster(int x, int y, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::core::vector3df position) :
	AEntity(x, y, MONSTER, position),
	AMovable()
{
	_3dModel = scene->addSphereSceneNode(3.0f, 32, 0, -1, position);
    _3dModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _3dModel->setMaterialTexture(0, driver->getTexture(getTexture("wallp002.jpg").c_str()));
	srand(time(NULL));
	_speed = 20.0f;
}

Monster::~Monster()
{
	_3dModel->remove();
}

void Monster::move(irr::core::vector3df)
{
}

void Monster::move(irr::f32 frame, AEntity &right, AEntity &left, AEntity &up, AEntity &down)
{
	if (_changeDir && _x%2 == 0 && _y%2 == 0) {
		_nodePosition.X = _x * 10;
		_nodePosition.Y = _y * 10;
		switch(rand()%4) {
			case 0:
				if (_y < 10 && (up == FLOOR || up == POWER_UP || up == PLAYER))
					_dir = UP;
				break;
			case 1:
				if (_y > 0 && (down == FLOOR || down == POWER_UP || down == PLAYER))
					_dir = DOWN;
				break;
			case 2:
				if (_x > 0 && (left == FLOOR || left == POWER_UP || left == PLAYER))
					_dir = LEFT;
				break;
			case 3:
				if (_x < 12 && (right == FLOOR || right == POWER_UP || right == PLAYER))
					_dir = RIGHT;
				break;
		}
		_changeDir = false;
	}

	switch (_dir) {
		case UP:
			if (_y < 10 && (up == FLOOR || up == POWER_UP || up == PLAYER)) {
				setNode(0, frame);
			} else if (rand()%2) {
				_dir = RIGHT;
			} else {
				_dir = LEFT;
			}
			break;
		case DOWN:
			if (_y > 0 && (down == FLOOR || down == POWER_UP || down == PLAYER))
				setNode(0, -frame);
			else if (rand()%2){
				_dir = LEFT;
			} else {
				_dir = RIGHT;
			}
			break;
		case LEFT:
			if (_x > 0 && (left == FLOOR || left == POWER_UP || left == PLAYER))
				setNode(-frame, 0);
			else if (rand()%2){
				_dir = UP;
			} else {
				_dir = DOWN;
			}
			break;
		case RIGHT:
			if (_x < 12 && (right == FLOOR || right == POWER_UP || right == PLAYER))
				setNode(frame, 0);
			else if (rand()%2){
				_dir = DOWN;
			} else {
				_dir = UP;
			}
			break;
	}
	_3dModel->setPosition(_nodePosition);
	_tik--;
}

void Monster::setNode(float x, float y)
{
	int tmpX = _x;
	int tmpY = _y;	
	_nodePosition.X += x * _speed;
	_nodePosition.Y += y * _speed;


	if (x > 0) {
		_x = (_nodePosition.X + 1) / 10;
	} else {
		_x = (_nodePosition.X + 9) / 10;
	}
	if (y > 0) {
		_y = (_nodePosition.Y + 1) / 10;
	} else {
		_y = (_nodePosition.Y + 9) / 10;
	}

	if (_x != tmpX || _y != tmpY)
		_changeDir = true;
}