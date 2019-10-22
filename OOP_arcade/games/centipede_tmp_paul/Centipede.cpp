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
	_dir(NONE),
	_fire(false),
	_tik(1)
{
	srand(time(NULL));
	_player = new std::pair<int, int>(((rand()%_board[0].size()/4) + _board[0].size()/4 * 3), rand()%_board.size());
	_board[_player->first][_player->second] = PLAYER;
	for (int x = 0; x < _board.size(); x++) {
		for (int y = 0; y < _board[0].size()/4 * 3; y++) {
			_board[y][x] = UNWALKABLE;
		}
	}
}

Centipede::~Centipede()
{
}

// === ACTIONS ===

void Centipede::left()
{
	_dir = LEFT;
}

void Centipede::right()
{
	_dir = RIGHT;
}

void Centipede::up()
{
	_dir = UP;
}

void Centipede::down()
{
	_dir = DOWN;
}

void Centipede::action()
{
	if (!_fire) {
		_shot = new std::pair<int, int>(_player->first-1, _player->second);
		_prev_shot = _board[_shot->first][_shot->second];
		_fire = true;
	}
}

// === RUN ===
void Centipede::update()
{
	// Player
	switch (_dir){
		case LEFT:
			if (_player->second > 0) {
				_board[_player->first][_player->second] = WALKABLE;
				_player->second--;
				_board[_player->first][_player->second] = PLAYER;
			}
			_dir = NONE;
			break;
		case RIGHT:
			if (_player->second < _board.size() - 1) {
				_board[_player->first][_player->second] = WALKABLE;
				_player->second++;
				_board[_player->first][_player->second] = PLAYER;
			}
			_dir = NONE;
			break;
		case UP:
			if (_board[_player->first - 1][_player->second] != UNWALKABLE) {
				_board[_player->first][_player->second] = WALKABLE;
				_player->first--;
				_board[_player->first][_player->second] = PLAYER;
			}
			_dir = NONE;
			break;
		case DOWN:
			if (_player->first < _board[0].size() - 1) {
				_board[_player->first][_player->second] = WALKABLE;
				_player->first++;
				_board[_player->first][_player->second] = PLAYER;
			}
			_dir = NONE;
			break;
	}

	// Shot
	if (_fire) {
		if (_shot->first == 0) {
			_board[_shot->first][_shot->second] = UNWALKABLE;
			delete(_shot);
			_fire = false;
		} else {
			switch (_board[_shot->first-1][_shot->second]) {
				case WALKABLE:
					_board[_shot->first][_shot->second] = _prev_shot;
					_shot->first--;
					_prev_shot = WALKABLE;
					_board[_shot->first][_shot->second] = SHOT;
					break;
				case UNWALKABLE:
					_board[_shot->first][_shot->second] = _prev_shot;
					_shot->first--;
					_prev_shot = UNWALKABLE;
					_board[_shot->first][_shot->second] = SHOT;
					break;
			}
		}
	}

	//Centipedes
	if (_centipedes.size() == 0)
		addCentipede();
	if(_tik == 1) {
		for (int i = 0; i < _centipedes.size(); i++) {
			moveCentipede(_centipedes[i]);
		}
		_tik = 0;
	}
	_tik++;
}

void Centipede::addCentipede()
{
	std::vector<std::pair<int, int>*> centipede;
	int size = rand()%5 + 5;

	for (int i = 0; i < size; i++) {
		centipede.push_back(new std::pair<int, int>(0, 0));
	}
	_centipedes.push_back(centipede);
}

void Centipede::moveCentipede(std::vector<std::pair<int, int>*> centipede)
{
	std::pair<int, int> *head;
	bool follow = false;

	for (std::pair<int, int> *pair : centipede) {
		for (int i = 0; i < _board.size(); i++) {
			if (_board[pair->first][i] == WALKABLE) {
				_board[pair->first][pair->second] = WALKABLE;
				break;
			}
			if (_board[pair->first][i] == UNWALKABLE) {
				_board[pair->first][pair->second] = UNWALKABLE;
				break;
			}
		}
		// HEAD
		if (!follow) {
			if (pair->second == 0) {
				if (_board[pair->first][pair->second + 1] == WALKABLE || _board[pair->first][pair->second + 1] == UNWALKABLE ) {
					pair->second++;
				} else {
					pair->first++;
				}
			} else if (pair->second == _board.size() - 1) {
				if (_board[pair->first][pair->second - 1] == WALKABLE || _board[pair->first][pair->second - 1] == UNWALKABLE ) {
					pair->second--;
				} else {
					pair->first++;
				}
			} else {
				if (_board[pair->first][pair->second + 1] == WALKABLE || _board[pair->first][pair->second + 1] == UNWALKABLE ) {
					pair->second++;
				} else if (_board[pair->first][pair->second - 1] == WALKABLE || _board[pair->first][pair->second - 1] == UNWALKABLE ) {
					pair->second--;
				}
			}
		// TAIL
		} else {
			if(head->first == pair->first) {
				if (head->second > pair->second) {
					if (_board[pair->first][pair->second + 1] == WALKABLE || _board[pair->first][pair->second + 1] == UNWALKABLE ) {
						pair->second++;
					}
				} else if (head->second < pair->second) {
					if (_board[pair->first][pair->second - 1] == WALKABLE || _board[pair->first][pair->second - 1] == UNWALKABLE ) {
						pair->second--;
					}
				}
			} else {
				if (pair->second == 0) {
					if (_board[pair->first + 1][pair->second] == WALKABLE || _board[pair->first + 1][pair->second] == UNWALKABLE) {
						pair->first++;
					}
				} else if (pair->second == _board.size() - 1) {
					if (_board[pair->first + 1][pair->second] == WALKABLE || _board[pair->first + 1][pair->second] == UNWALKABLE) {
						pair->first++;
					}
				} else {
					if (head->second > pair->second) {
						if (_board[pair->first + 1][pair->second] == ENNEMY) {
							if (_board[pair->first][pair->second - 1] == WALKABLE || _board[pair->first][pair->second - 1] == UNWALKABLE ) {
							pair->second--;
							}
						} else {
							if (_board[pair->first][pair->second + 1] == WALKABLE || _board[pair->first][pair->second + 1] == UNWALKABLE ) {
								pair->second++;
							}
						}
					} else if (head->second < pair->second) {
						if (_board[pair->first + 1][pair->second] == ENNEMY) {
							if (_board[pair->first][pair->second + 1] == WALKABLE || _board[pair->first][pair->second + 1] == UNWALKABLE ) {
								pair->second++;
							}
						} else {
							if (_board[pair->first][pair->second - 1] == WALKABLE || _board[pair->first][pair->second - 1] == UNWALKABLE ) {
								pair->second--;
							}
						}
					} else {
						if (_board[head->first][pair->second + 1] == ENNEMY) {
							if (_board[pair->first][pair->second + 1] == WALKABLE || _board[pair->first][pair->second + 1] == UNWALKABLE ) {
								pair->second++;
							}
						} else {
							if (_board[pair->first][pair->second - 1] == WALKABLE || _board[pair->first][pair->second - 1] == UNWALKABLE ) {
								pair->second--;
							}
						}
					}
				}
			}
		}
		_board[pair->first][pair->second] = ENNEMY;

		if (!follow) {
			head = pair;
			follow = true;
		}
		
	}
}