/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Centipede
*/

#include "Centipede.hpp"

extern "C" IGame *start()
{
	return new Centipede;
}

Centipede::Centipede() : 
	AGame(),
	_tik(899),
	_gameOver(false)
{
	srand(time(NULL));
	_player = new Player(((rand()%_board[0].size()/4) + _board[0].size()/4 * 3), rand()%_board.size());
	setPos(_player->getPosX(), _player->getPosY(), PLAYER);
	for (int x = 0; x < _board.size(); x++) {
		for (int y = 0; y < _board[0].size()/4 * 3; y++) {
			_board[y][x] = UNWALKABLE;
		}
	}
	_objects.push_back(new Brick(20, 40));
	_objects.back()->setGround(UNWALKABLE);
	_objects.back()->setMap(_board);
}

Centipede::~Centipede()
{
	delete _player;
}

// === ACTIONS ===

bool Centipede::check_out_of_bound(Object *obj, int i, int j)
{
	if (obj->getPosX() + i < 0 ||
		obj->getPosX() + i >= _board.size())
		return (false);
	if (obj->getPosY() + j < 0 ||
		obj->getPosY() + j >= _board[0].size())
		return (false);
	return (true);
}

void Centipede::left()
{
	setPos(_player->getPosX(), _player->getPosY(), WALKABLE);
	if (check_out_of_bound(_player, 0, -1))
		_player->move(0, -1);
	setPos(_player->getPosX(), _player->getPosY(), PLAYER);
}

void Centipede::right()
{
	setPos(_player->getPosX(), _player->getPosY(), WALKABLE);
	if (check_out_of_bound(_player, 0, 1))
		_player->move(0, 1);
	setPos(_player->getPosX(), _player->getPosY(), PLAYER);
}

void Centipede::up()
{
	setPos(_player->getPosX(), _player->getPosY(), WALKABLE);
	if (_board[_player->getPosX() - 1][_player->getPosY()] == WALKABLE)
		_player->move(-1, 0);
	setPos(_player->getPosX(), _player->getPosY(), PLAYER);
}

void Centipede::down()
{
	setPos(_player->getPosX(), _player->getPosY(), WALKABLE);
	if (check_out_of_bound(_player, 1, 0))
		_player->move(1, 0);
	setPos(_player->getPosX(), _player->getPosY(), PLAYER);
}

void Centipede::createWorm(std::vector<Object*> &_objects)
{
	_objects.push_back(new Worm());
	_objects.back()->setGround(UNWALKABLE);
}

void Centipede::hit(int x, int y)
{
	int part;
	std::vector<Bodypart> *temp_part;

	for (unsigned i = 0; i < _objects.size(); i++) {
		if ((part = (_objects[i]->isThere(x, y))) != 0) {
			std::cout << part << std::endl;
			if (_objects[i]->getType() == EAT) {
				(static_cast<Brick *>(_objects[i]))->gotHit();
				if ((static_cast<Brick *>(_objects[i]))->getHp() <= 0) {
					_objects[i]->unsetMap(_board);
					_objects.erase(_objects.begin() + i);
				}
				return;
			} else if (_objects[i]->getType() == ENNEMY) {
				temp_part = (static_cast<Worm *>(_objects[i]))->getBody(part - 2);
				for (Object &wo : *temp_part) {
					wo.unsetMap(_board);
					_objects.push_back(new Brick(wo.getPosX(), wo.getPosY()));
					_objects.back()->setGround(UNWALKABLE);
					_objects.back()->setMap(_board);
				}
				delete(temp_part);
				if (part == 1) {
					_objects.push_back(new Brick(_objects[i]->getPosX(), _objects[i]->getPosY()));
					_objects.back()->setMap(_board);
					_objects.back()->setGround(UNWALKABLE);
					_objects.erase(_objects.begin() + i);
				} else {
					(static_cast<Worm *>(_objects[i]))->cut(part - 2);
				}
				return;
			}
		}
	}
}

void Centipede::updateBullet(Bullet &bullet)
{
	if (bullet.isActive()) {
		bullet.unsetMap(_board);
		if (!check_out_of_bound(&bullet, - 1, 0)) {
			bullet.setActive(false);
		} else if (_board[bullet.getPosX() - 1][bullet.getPosY()] == WALKABLE ||
					_board[bullet.getPosX() - 1][bullet.getPosY()] == UNWALKABLE) {
			bullet.move(-1, 0);
			bullet.setMap(_board);
		} else {
			bullet.setActive(false);
			hit(bullet.getPosX() - 1, bullet.getPosY());
		}
	}
}

bool Centipede::updateWorm(Worm *worm)
{
	std::vector<Bodypart> *temp_part;
	
	if (!check_out_of_bound(worm, 0, 1 * worm->getDir())) {
		if (!check_out_of_bound(worm, 1, 0)) {
			_gameOver = true;
			return true;
		}
		worm->setDir(worm->getDir() * -1);
		worm->swarm(1, 0, _board);
	} else if (_board[worm->getPosX()][worm->getPosY() + 1 * worm->getDir()] == EAT) {
		worm->setDir(worm->getDir() * -1);
		worm->swarm(1, 0, _board);
	} else if (_board[worm->getPosX()][worm->getPosY() + 1 * worm->getDir()] == PLAYER) {
		_gameOver = true;
		return true;
	} else if (_board[worm->getPosX()][worm->getPosY() + 1 * worm->getDir()] == SHOT) {
		temp_part = worm->getBody(-1);
		for (Object &wo : *temp_part) {
			wo.unsetMap(_board);
			_objects.push_back(new Brick(wo.getPosX(), wo.getPosY()));
			_objects.back()->setGround(UNWALKABLE);
			_objects.back()->setMap(_board);
		}
		delete(temp_part);
		_objects.push_back(new Brick(worm->getPosX(), worm->getPosY()));
		_objects.back()->setMap(_board);
		_objects.back()->setGround(UNWALKABLE);
		return (false);
	} else {
		worm->swarm(0, 1 * worm->getDir(), _board);
	}
	return (true);
}

void Centipede::update()
{
	if (!_gameOver) {
		_tik++;
		if (_tik == 900) {
			_tik = 0;
			createWorm(_objects);
		}

		if (_player->getBullet().isActive()) {
			updateBullet(_player->getBullet());
		}

		if (_tik % 5 == 0) {
			for (unsigned i = 0; i < _objects.size(); i++) {
				if (_objects[i]->getType() == ENNEMY) {
					if (!updateWorm(static_cast<Worm *>(_objects[i])))
						_objects.erase(_objects.begin() + i);
				}
			}
		}
	} else {
		// say game over maybe
	}
}

void Centipede::action()
{
	if (_player->getBullet().isActive() == false) {
		_player->getBullet().setPos(_player->getPosX(), _player->getPosY());
		_player->getBullet().setGround(_board[_player->getBullet().getPosX()][_player->getBullet().getPosY()]);
		_player->getBullet().setActive(true);
	}
	std::cout << "list" << std::endl;
	for (auto &i : _objects) {
		std::cout << "obj : " << i->getType() << std::endl;
	}
}