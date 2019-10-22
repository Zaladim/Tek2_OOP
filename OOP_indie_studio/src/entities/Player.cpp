/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Player
*/

#include "Player.hpp"

int Player::cpt = 0;

Player::Player(int x, int y, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::f32 r, irr::s32 bit, int b, irr::core::vector3df position, irr::scene::IMetaTriangleSelector *metaSelector, int score, int id) : 
	AEntity(x, y, PLAYER, position),
	AMovable(),
	_metaSelector(metaSelector),
	_startX(x),
	_startY(y),
	_score(score)
{
	if (id < 0) {
		_id = cpt;
		cpt++;
	} else {
		_id = id;
	}
    if (_id == 1)
	    _3dModel = scene->addAnimatedMeshSceneNode(scene->getMesh(getTexture("bomberman2.x").c_str()),(irr::scene::ISceneNode *) 0, (irr::s32)_id, position, irr::core::vector3df(270, 0, 0), irr::core::vector3df(15.0f, 15.0f, 15.0f));
    else
	    _3dModel = scene->addAnimatedMeshSceneNode(scene->getMesh(getTexture("bomberman1.x").c_str()),(irr::scene::ISceneNode *) 0, (irr::s32)_id, position, irr::core::vector3df(270, 0, 0), irr::core::vector3df(15.0f, 15.0f, 15.0f));
    _3dModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_3dModel->setRotation(irr::core::vector3df(270, 0, 90));
    selector = scene->createTriangleSelectorFromBoundingBox(_3dModel);
    _3dModel->setTriangleSelector(selector);
    _metaSelector->addTriangleSelector(selector);
    _anim = scene->createCollisionResponseAnimator(_metaSelector, _3dModel, irr::core::vector3df(3.5, 3.5, 1), irr::core::vector3df(0.0f, 0.0f, 0.0f));
    _3dModel->addAnimator(_anim);
	selector->drop();
}

Player::~Player()
{
    _3dModel->remove();
	selector->drop();
}



int Player::getId() const
{
	return _id;
}

float Player::getSpeed() const
{
	return _speed;
}

int Player::getScore() const
{
	return _score;
}

int Player::getBomb() const
{
	return _bomb;
}

int Player::getMaxBomb() const {
	return _bombMax;
}

bool Player::getwallPass() const
{
	return _wallPass;
}

void Player::addScore(int score)
{
	_score += score;
}

void Player::reset()
{
	_nodePosition.X = _startX * 10;
	_nodePosition.Y = _startY * 10;
	_x = _startX;
	_y = _startY;
	_3dModel->setPosition(_nodePosition);
}

void Player::move(irr::core::vector3df position)
{
    _x = position.X / 10;
    _y = position.Y / 10;

    if (int(position.X) % 10 > 5)
        _x += 1;
    if(int(position.Y) % 10 > 5)
        _y += 1;
}

std::unique_ptr<Bomb> Player::bomb(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver)
{
	std::unique_ptr<Bomb> bomb;


	if(_bomb > 0 ){
		_bomb--;
		bomb.reset(new Bomb(_x * 10, _y * 10, _power, _id, scene, driver, _metaSelector));
	} else {
		bomb.reset(nullptr);
	}
	_nodePosition.X = _x * 10;
	_nodePosition.Y = _y * 10;
	return bomb;
}

void Player::addPower(power_type type)
{
	switch (type) {
		case BOMBUP:
			if (_bombMax < 5) {
				_bombMax ++;
				_bomb ++;
			}
			break;
		case FIREUP:
			if (_power < 5) {
				_power ++;
			}
			break;
		case SPEEDUP:
			if (_speed < 60.0) {
				_speed += 5.0;
			}
			break;
		case WALLUP:
			_wallPass = true;
			break;
	}
}

void Player::addBomb()
{
	if (_bomb < _bombMax)
		_bomb++;
}

void Player::setNode(float x, float y, std::vector<std::unique_ptr<AEntity>> &bombs)
{
	irr::core::vector3df reset = _nodePosition;
	int resetX = _x;
	int resetY = _y;
	bool collide = false;

	for (auto &b : bombs) {
		if (x > 0) {
			if (_nodePosition.X + x * _speed > b->getX() - 10 && _nodePosition.X + x * _speed <= b->getX() && \
			_nodePosition.Y + y * _speed > b->getY() - 10 && _nodePosition.Y + y * _speed <= b->getY()) {
				collide = true;
				break;
			}
		}
		if (y > 0) {
			if (_nodePosition.X + x * _speed > b->getX() - 10 && _nodePosition.X + x * _speed <= b->getX() && \
			_nodePosition.Y + y * _speed > b->getY() - 10 && _nodePosition.Y + y * _speed <= b->getY()) {
				collide = true;
				break;
			}
		}
		if (x < 0) {
			if (_nodePosition.X + x * _speed > b->getX() && _nodePosition.X + x * _speed <= b->getX() + 10 && \
			_nodePosition.Y + y * _speed > b->getY() && _nodePosition.Y + y * _speed <= b->getY() + 10) {
				collide = true;
				break;
			}
		}
		if (y < 0) {
			if (_nodePosition.X + x * _speed > b->getX() && _nodePosition.X + x * _speed <= b->getX() + 10 && \
			_nodePosition.Y + y * _speed > b->getY() && _nodePosition.Y + y * _speed <= b->getY() + 10) {
				collide = true;
				break;
			}
		}
		// if (x < 0 || y < 0) {
		// 	if (_nodePosition.X + x * _speed > b->getX() + 10 && _nodePosition.X + x * _speed <= b->getX() && \
		// 		_nodePosition.Y + y * _speed > b->getY() + 10 && _nodePosition.Y + y * _speed <= b->getY()) {
		// 		collide = true;
		// 		break;
		// 	}
		// }
	}

	if (!collide) {
		if ((x > 0 && _x < 12) || (x < 0 && _x > 0)) {
			_nodePosition.X += x * _speed;
		}
		if ((y > 0 && _y < 10) || (y < 0 && _y > 0)) {
			_nodePosition.Y += y * _speed;
		}

		if (x > 0) {
			_x = (_nodePosition.X + 2) / 10;
		} else {
			_x = (_nodePosition.X + 8) / 10;
		}
		if (y > 0) {
			_y = (_nodePosition.Y + 2) / 10;
		} else {
			_y = (_nodePosition.Y + 8) / 10;
		}
		// if (_x != resetX || _y != resetY) {
		// 	for (auto &b : bombs) {
		// 		if (_x == b->getX() / 10 && _y == b->getY() / 10) {
		// 			_nodePosition = reset;
		// 			_x = resetX;
		// 			_y = resetY;
		// 		}
		// 	}
		// }
	}
	//_Skin->setPosition(_nodePosition);
}

void Player::setDirection(direction_t direction)
{
	_3dModel->setRotation(irr::core::vector3df(270, 0, 90 * direction));
}