/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Game board
*/

#include "Board.hpp"

Board::Board(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, int players) :
_gen(_x, _y)
{
	std::vector<std::vector<int>> board = _gen.generate(0, 50);

	for (int i = 0; i < _x; i++) {
		std::vector<std::unique_ptr<AEntity>> tmp;
		for (int j = 0; j < _y; j++) {
			if (board[i][j] == WALL)
				tmp.push_back(std::unique_ptr<AEntity> (new Wall(i, j)));
			else if (board[i][j] == SOFT)
				tmp.push_back(std::unique_ptr<AEntity> (new Soft(i, j, scene, driver)));
			else
				tmp.push_back(std::unique_ptr<AEntity> (new Floor(i, j)));
		}
		_entities.push_back(std::move(tmp));
	}
	_players.push_back(std::unique_ptr<AEntity> (new Player(0, 10, scene, driver, 5.0f, 32, -1, irr::core::vector3df(0.0f, 100.0f, 20.0f))));
	if (players > 1) 
   		_players.push_back(std::unique_ptr<AEntity> (new Player(12, 0, scene, driver, 5.0f, 32, -1, irr::core::vector3df(120.0f, 0.0f, 20.0f))));
	_monsters.push_back(std::unique_ptr<AEntity> (new Monster(0, 0, scene, driver, irr::core::vector3df(0.0f, 0.0f, 20.0f))));
	// _players.push_back(std::unique_ptr<AEntity> (new Player(0, 10, scene, driver, 5.0f, 32, -1, irr::core::vector3df(0.0f, 100.0f, 20.0f))));
}

// Board::Board(const BoardGenerator &gen, \
// 			const std::vector<std::vector<std::unique_ptr<AEntity>>> &entities, \
// 			const std::vector<std::unique_ptr<AEntity>> &players, \
// 			const std::vector<std::unique_ptr<AEntity>> &monsters, \
// 			const std::vector<std::unique_ptr<AEntity>> &bombs) : 
// 	_gen(gen),
// 	_entities(std::move(entities)),
// 	_players(std::move(players)),
// 	_monsters(std::move(monsters)),
// 	_bombs(std::move(bombs))
// {
// }

Board::~Board()
{
}

int Board::getX() const
{
	return _x;
}

int Board::getY() const
{
	return _y;
}

void Board::setPos(int x, int y, AEntity *entity)
{
	if (entity) {
		if (*entity == PLAYER || *entity == BOMB) {
			entity->destroy();
		} else 
			_entities[x][y].reset(entity);
	}
}

AEntity *Board::getPos(int x, int y)
{
	return _entities[x][y].get();
}

bool Board::checkBomb(int x, int y)
{
	for (auto &b : _bombs) {
		if (b->getX()/10 == x && b->getY()/10 == y)
			return true;
	}
	return false;
}

void Board::newEntity(std::unique_ptr<AEntity> entity)
{
	if (*entity == BOMB) {
		_bombs.push_back(std::move(entity));
	}
}


int Board::update()
{
	long unsigned int i = 0;

	while (i < _players.size()) {
		AEntity *tmp(_players[i]->update());
		
		if (_players[i].get() != tmp) {
			if (tmp == nullptr) {
				_players.erase(_players.begin() + i);
			} else if (*tmp == BOMB) {
				_bombs.push_back(std::unique_ptr<AEntity>(tmp));
				i++;
			} else {
				_players[i].reset(tmp);
				i++;
			}
		} else {
			if (*_entities[_players[i]->getX()][_players[i]->getY()] == POWER_UP) {
				std::cout << "PowerUp : " << dynamic_cast<PowerUp *>(_entities[_players[i]->getX()][_players[i]->getY()].get())->getType() << std::endl;
				dynamic_cast<Player *>(_players[i].get())->addPower(dynamic_cast<PowerUp *>(_entities[_players[i]->getX()][_players[i]->getY()].get())->getType());
				setPos(_players[i]->getX(), _players[i]->getY(), _entities[_players[i]->getX()][_players[i]->getY()]->destroy());
			}
			i++;
		}
		//std::cout<<"bcl_player_board: i="<<i<<" and playeri="<<std::endl;
	}

	i = 0;
	while (i < _monsters.size()) {
		AEntity *tmp(_monsters[i]->update());
		
		if (_monsters[i].get() != tmp) {
			if (tmp == nullptr) {
				_monsters.erase(_monsters.begin() + i);
			} else {
				_monsters[i].reset(tmp);
			}
		} else {
			i++;
		}

	}
	
	i = 0;
	while (i < _bombs.size()) {
		AEntity *tmp(_bombs[i]->update());
		
		if (_bombs[i].get() != tmp) {
			if (tmp == nullptr) {
                std::cout << "eeeee" << std::endl;
				if (explode(_bombs[i]->getX() / 10, _bombs[i]->getY() / 10, dynamic_cast<Bomb *>(_bombs[i].get())->getPower()))
					return 1;
				for (int j = 0; j < _players.size(); j++) {
					std::cout << dynamic_cast<Player *>(_players[j].get())->getId() << " -- " << dynamic_cast<Bomb *>(_bombs[i].get())->getId() << std::endl;
					if (dynamic_cast<Player *>(_players[j].get())->getId() == dynamic_cast<Bomb *>(_bombs[i].get())->getId()) {
						dynamic_cast<Player *>(_players[j].get())->addBomb();
						break;
					}
				}
				std::cout << "Bomb? : " << _bombs[i]->getEntity() << std::endl;
				std::cout << "Size : " << _bombs.size() << std::endl;
				_bombs[i].reset();
				_bombs.erase(_bombs.begin() + i);
				std::cout << "Size : " << _bombs.size() << std::endl;
			} else {
				_bombs[i].reset(tmp);
                std::cout << "ppppp" << std::endl;
			}
		} else {
			i++;
		}
	}
	return 0;
	//std::cout<<"bcl_bomb_board"<<std::endl;
}

int Board::explode(int x, int y, int power)
{
	std::cout << "TEST : " << power << std::endl;
	for (int i = 1; i <= power && x - i >= 0; i++) {
		std::cout << x - i << " - " << y << std::endl;
		std::cout << (*this)(x - i, y).getEntity() << std::endl;
		if ((*this)(x - i, y) == WALL) {
			break;
		}
		if ((*this)(x - i, y) == PLAYER) {
			return 1;
		}
		if ((*this)(x - i, y) == BOMB) {
			(*this)(x - i, y).destroy();
			continue;
		}
		while ((*this)(x - i, y) != FLOOR && (*this)(x - i, y) != POWER_UP ) {
			setPos(x - i, y, (*this)(x - i, y).destroy());
		}
	}
	for (int i = 1; i <= power && x + i < MAXX; i++) {
		std::cout << x + i << " - " << y << std::endl;
		std::cout << (*this)(x + i, y).getEntity() << std::endl;
		if ((*this)(x + i, y) == WALL) {
			break;
		}
		if ((*this)(x + i, y) == PLAYER) {
			return 1;
		}
		if ((*this)(x + i, y) == BOMB) {
			(*this)(x + i, y).destroy();
			continue;
		}
		while ((*this)(x + i, y) != FLOOR && (*this)(x + i, y) != POWER_UP ) {
			setPos(x + i, y, (*this)(x + i, y).destroy());
		}
	}
	for (int i = 1; i <= power && y - i >= 0; i++) {
		std::cout << x << " - " << y - i << std::endl;
		std::cout << (*this)(x, y - i).getEntity() << std::endl;
		if ((*this)(x, y - i) == WALL) {
			break;
		}
		if ((*this)(x, y - i) == PLAYER) {
			return 1;
		}
		if ((*this)(x, y - i) == BOMB) {
			(*this)(x, y - i).destroy();
			continue;
		}
		while ((*this)(x, y - i) != FLOOR && (*this)(x, y - i) != POWER_UP ) {
			setPos(x, y - i, (*this)(x, y - i).destroy());
		}
	}
	for (int i = 1; i <= power && y + i < MAXY; i++) {
		std::cout << x << " - " << y + i << std::endl;
		std::cout << (*this)(x, y + i).getEntity() << std::endl;
		if ((*this)(x, y + i) == WALL) {
			break;
		}
		if ((*this)(x, y + i) == PLAYER) {
			return 1;
		}
		if ((*this)(x, y + i) == BOMB) {
			(*this)(x, y + i).destroy();
			continue;
		}
		while ((*this)(x, y + i) != FLOOR && (*this)(x, y + i) != POWER_UP ) {
			setPos(x, y + i, (*this)(x, y + i).destroy());
		}
	}
	std::cout << "ENDTEST" << std::endl;
	return 0;
}

AEntity &Board::operator()(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAXX || y >= MAXY) {
		Floor tmp(0, 0);
		return tmp;
	}

	for (auto &p : _players) {
		if (x == p->getX() && y == p->getY())
			return *(p.get());
	}
	for (auto &m : _monsters) {
		if (x == m->getX() && y == m->getY())
			return *(m.get());
	}
	for (auto &b : _bombs) {
		if (x == (b->getX() / 10) && y == (b->getY() / 10))
			return *(b.get());
	}
	return *(getPos(x, y));
}