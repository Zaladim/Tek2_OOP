/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Game board
*/

#include "Board.hpp"

Board::Board(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector, Sound &soundBox, int players) :
_gen(_x, _y),
_soundBox(soundBox),
_playerCounted(-1)
{
	std::vector<std::vector<int>> board = _gen.generate(0, 50);

	for (int i = 0; i < _x; i++) {
		std::vector<std::unique_ptr<AEntity>> tmp;
		for (int j = 0; j < _y; j++) {
			if (board[i][j] == WALL)
				tmp.push_back(std::unique_ptr<AEntity> (new Wall(i, j, scene, driver, metaSelector)));
			else if (board[i][j] == SOFT)
				tmp.push_back(std::unique_ptr<AEntity> (new Soft(i, j, scene, driver, metaSelector)));
			else
				tmp.push_back(std::unique_ptr<AEntity> (new Floor(i, j)));
		}
		_entities.push_back(std::move(tmp));
	}
	_players.push_back(std::unique_ptr<AEntity> (new Player(0, 10, scene, driver, 4.0f, 32, -1, irr::core::vector3df(0.0f, 100.0f, 20.0f), metaSelector, 0, 0)));
	if (players > 1)
   		_players.push_back(std::unique_ptr<AEntity> (new Player(12, 0, scene, driver, 4.0f, 32, -1, irr::core::vector3df(120.0f, 0.0f, 20.0f), metaSelector, 0, 1)));
	generateMonsters(1, scene, driver);
}

Board::Board(std::string save, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector, Sound &soundBox) :
_gen(_x, _y),
_soundBox(soundBox),
_playerCounted(0)
{
	for (int i = 0; i < _x; i++) {
		std::vector<std::unique_ptr<AEntity>> tmp;
		for (int j = 0; j < _y; j++) {
			tmp.push_back(std::unique_ptr<AEntity> (new Floor(i, j)));
		}
		_entities.push_back(std::move(tmp));
	}

	std::ifstream file;
	file.open(save);
	std::string line;
	int x;
	int y;
	int score;
	int type;
	int lvl;

	while(file.is_open() && file >> line) {
		if (line == "player") {
			file >> x;
			file >> y;
			file >> score;
			file >> type;
			_players.push_back(std::unique_ptr<AEntity> (new Player(x, y, scene, driver, 4.0f, 32, -1, irr::core::vector3df(x * 10, y * 10, 20.0f), metaSelector, score, type)));
			_playerCounted ++;
		}
		if (line == "wall") {
			file >> x;
			file >> y;
			setPos(x, y, new Wall(x, y, scene, driver, metaSelector));
		}
		if (line == "soft") {
			file >> x;
			file >> y;
			setPos(x, y, new Soft(x, y, scene, driver, metaSelector));
		}
		if (line == "powerup") {
			file >> x;
			file >> y;
			file >> type;
			setPos(x, y, new PowerUp(x, y, static_cast<power_type>(type), scene, driver));
		}
		if (line == "monster") {
			file >> x;
			file >> y;
			_monsters.push_back(std::unique_ptr<AEntity> (new Monster(x, y, scene, driver, irr::core::vector3df(x * 10, y * 10, 20.0f))));
		}
		if (line == "level") {
			file >> _level;
		}
	}
	file.close();
}


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

int Board::getLevel() const
{
	return (_level);
}

void Board::setLevel(int level)
{
	_level = level;
}

bool Board::checkBomb(int x, int y)
{
	for (auto &b : _bombs) {
		if (b->getX()/10 == x && b->getY()/10 == y)
			return true;
	}
	return false;
}

bool Board::checkMonster(int x, int y)
{
	for (auto &m : _monsters) {
		if (m->getX() == x && m->getY() == y)
			return true;
	}
	return false;
}

void Board::newLevel(int level, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector)
{
	for (auto &elem : _entities) {
		elem.clear();
	}
	_entities.clear();
	_monsters.clear();
	_bombs.clear();
	_explosion.clear();

	_players.push_back(std::unique_ptr<AEntity> (new Player(0, 10, scene, driver, 4.0f, 32, -1, irr::core::vector3df(0.0f, 100.0f, 20.0f), metaSelector, dynamic_cast<Player *>(_players[0].get())->getScore(), dynamic_cast<Player *>(_players[0].get())->getId())));
	_players.erase(_players.begin());
	if (_players.size() > 1) {
		_players.push_back(std::unique_ptr<AEntity> (new Player(12, 0, scene, driver, 4.0f, 32, -1, irr::core::vector3df(120.0f, 0.0f, 20.0f), metaSelector, dynamic_cast<Player *>(_players[0].get())->getScore(), dynamic_cast<Player *>(_players[0].get())->getId())));
		_players.erase(_players.begin());
	}

	int wall = (level / 5) * 5;
	int soft = (level / 3) * 2 + 50;


	std::vector<std::vector<int>> board = _gen.generate(wall, soft);
	for (int i = 0; i < _x; i++) {
		std::vector<std::unique_ptr<AEntity>> tmp;
		for (int j = 0; j < _y; j++) {
			if (board[i][j] == WALL)
				tmp.push_back(std::unique_ptr<AEntity> (new Wall(i, j, scene, driver, metaSelector)));
			else if (board[i][j] == SOFT)
				tmp.push_back(std::unique_ptr<AEntity> (new Soft(i, j, scene, driver, metaSelector)));
			else
				tmp.push_back(std::unique_ptr<AEntity> (new Floor(i, j)));
		}
		_entities.push_back(std::move(tmp));
	}
	generateMonsters(level, scene, driver);
}

void Board::death()
{
	for (auto &elem : _entities) {
		elem.clear();
	}
	_entities.clear();
	_monsters.clear();
	_bombs.clear();
	_explosion.clear();

	while (_players.size() > 0) {
		_players.erase(_players.begin());
	}

}

boost::filesystem::path Board::saveGame(std::string name_save)
{
	std::ofstream file;
	boost::filesystem::path p("save");
	p/=name_save;
	file.open(p.c_str());

	if (file.is_open()) {
		for (auto &p : _players) {
			file << "player " << p->getX() << " " << p->getY() << " " << dynamic_cast<Player *>(p.get())->getScore() << " " << dynamic_cast<Player *>(p.get())->getId() << std::endl;
			_playerCounted++;
		}
		for (auto &m : _monsters) {
			file << "monster " << m->getX() << " " << m->getY() << std::endl;
		}
		for (int i = 0; i < _x; i++) {
			for (int j = 0; j < _y; j++) {
				switch (_entities[i][j]->getEntity()) {
					case WALL:
						file << "wall " << _entities[i][j]->getX() << " " << _entities[i][j]->getY() << std::endl;
						break;
					case SOFT:
						file << "soft " << _entities[i][j]->getX() << " " << _entities[i][j]->getY() << std::endl;
						break;
					case POWER_UP:
						file << "powerup " << _entities[i][j]->getX() << " " << _entities[i][j]->getY() << " " << dynamic_cast<PowerUp *>(_entities[i][j].get())->getType() << std::endl;
						break;
				}
			}
		}
		file << "level " << _level << std::endl;
	}
	file.close();
	return (p);
}

void Board::newEntity(std::unique_ptr<AEntity> entity)
{
	if (*entity == BOMB) {
		_bombs.push_back(std::move(entity));
	}
}

void Board::generateMonsters(int nb, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver)
{
	while (nb > 0) {
		for (int x = 2; x < MAXX - 2 && nb > 0; x++) {
			for (int y = 2; y < MAXY - 2 && nb > 0; y++) {
				if ((*this)(x, y) == FLOOR && std::rand()%100 == 1) {
					_monsters.push_back(std::unique_ptr<AEntity> (new Monster(x, y, scene, driver, irr::core::vector3df(x * 10, y * 10, 20.0f))));
					nb--;
				}
			}
		}
	}
}


int Board::update(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver)
{
	long unsigned int i = 0;

	while (i < _players.size()) {
		AEntity *tmp(_players[i]->update());

		if (checkMonster(_players[i]->getX(), _players[i]->getY())) {
			_soundBox.play(DEAD);
			return 1;
		}

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
				dynamic_cast<Player *>(_players[i].get())->addPower(dynamic_cast<PowerUp *>(_entities[_players[i]->getX()][_players[i]->getY()].get())->getType());
				setPos(_players[i]->getX(), _players[i]->getY(), _entities[_players[i]->getX()][_players[i]->getY()]->destroy());
			}
			i++;
		}
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
				int score = explode(_bombs[i]->getX() / 10, _bombs[i]->getY() / 10, dynamic_cast<Bomb *>(_bombs[i].get())->getPower(), dynamic_cast<Bomb *>(_bombs[i].get())->getId(), scene, driver);
				if (score%10 >= 1) {
					_soundBox.play(DEAD);
					for (int j = 0; j < _players.size() && _players.size() > 1; j++) {
						if (dynamic_cast<Player *>(_players[j].get())->getId() == dynamic_cast<Bomb *>(_bombs[i].get())->getId()) {
							dynamic_cast<Player *>(_players[j].get())->addScore(score - score%10);
						}
					}
					return 1;
				}
				for (int j = 0; j < _players.size(); j++) {
					if (dynamic_cast<Player *>(_players[j].get())->getId() == dynamic_cast<Bomb *>(_bombs[i].get())->getId()) {
						dynamic_cast<Player *>(_players[j].get())->addBomb();
						dynamic_cast<Player *>(_players[j].get())->addScore(score);
						if (score > 1) {
							_soundBox.play(KILL);
						}
						break;
					}
				}
				_bombs[i].reset();
				_bombs.erase(_bombs.begin() + i);
			} else {
				_bombs[i].reset(tmp);
			}
		} else {
			i++;
		}
	}

	i = 0;
	while(i < _explosion.size()) {
		if (_explosion[i]->update() == 0) {
			_explosion.erase(_explosion.begin() + i);
		} else {
			i++;
		}
	}


	return 0;
}

int Board::explode(int x, int y, int power, int id, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver)
{
	int score = 0;

	_soundBox.play(EXPL);

	_explosion.push_back(std::unique_ptr<Explosion> (new Explosion(x, y, scene, driver)));
	for (int i = 1; i <= power && x - i >= 0; i++) {
		if ((*this)(x - i, y) == WALL) {
			break;
		}
		_explosion.push_back(std::unique_ptr<Explosion> (new Explosion(x - i, y, scene, driver)));
		if ((*this)(x - i, y) == PLAYER) {
			for (auto &elem : _players) {
				if (elem->getX() == x - i && elem->getY() == y && dynamic_cast<Player *>(elem.get())->getId() != id) {
					score += 100;
				}
			}
			score += 1;
			continue;
		}
		if ((*this)(x - i, y) == MONSTER) {
			(*this)(x - i, y).destroy();
			score += 10;
			continue;
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
		if ((*this)(x + i, y) == WALL) {
			break;
		}
		_explosion.push_back(std::unique_ptr<Explosion> (new Explosion(x + i, y, scene, driver)));
		if ((*this)(x + i, y) == PLAYER) {
			for (auto &elem : _players) {
				if (elem->getX() == x + i && elem->getY() == y && dynamic_cast<Player *>(elem.get())->getId() != id) {
					score += 100;
				}
			}
			score += 1;
			continue;
		}
		if ((*this)(x + i, y) == MONSTER) {
			(*this)(x + i, y).destroy();
			score += 10;
			continue;
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
		if ((*this)(x, y - i) == WALL) {
			break;
		}
		_explosion.push_back(std::unique_ptr<Explosion> (new Explosion(x, y - i, scene, driver)));
		if ((*this)(x, y - i) == PLAYER) {
			for (auto &elem : _players) {
				if (elem->getX() == x && elem->getY() == y - i && dynamic_cast<Player *>(elem.get())->getId() != id) {
					score += 100;
				}
			}
			score += 1;
			continue;
		}
		if ((*this)(x, y - i) == MONSTER) {
			(*this)(x, y - i).destroy();
			score += 10;
			continue;
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
		if ((*this)(x, y + i) == WALL) {
			break;
		}
		_explosion.push_back(std::unique_ptr<Explosion> (new Explosion(x, y + i, scene, driver)));
		if ((*this)(x, y + i) == PLAYER) {
			for (auto &elem : _players) {
				if (elem->getX() == x && elem->getY() == y + i && dynamic_cast<Player *>(elem.get())->getId() != id) {
					score += 100;
				}
			}
			score += 1;
			continue;
		}
		if ((*this)(x, y + i) == MONSTER) {
			(*this)(x, y + i).destroy();
			score += 10;
			continue;
		}
		if ((*this)(x, y + i) == BOMB) {
			(*this)(x, y + i).destroy();
			continue;
		}
		while ((*this)(x, y + i) != FLOOR && (*this)(x, y + i) != POWER_UP ) {
			setPos(x, y + i, (*this)(x, y + i).destroy());
		}
	}
	return score;
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