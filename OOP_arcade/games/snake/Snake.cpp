/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Snake
*/

#include "Snake.hpp"
#include <iostream>

extern "C" IGame *start()
{
	return new Snake;
}

Snake::Snake() : 
	AGame(),
	_face(RIGHT),
	_tik(0),
	_gameOver(false)
{
	_snake.push(*new std::pair<int, int>(_board.size()/2-1, _board[0].size()/2));
	_snake.push(*new std::pair<int, int>(_board.size()/2, _board[0].size()/2));
	_snake.push(*new std::pair<int, int>(_board.size()/2+1, _board[0].size()/2));
	_snake.push(*new std::pair<int, int>(_board.size()/2+2, _board[0].size()/2));
	srand(time(0));
	new_pellet();
	_board[_snake.front().first][_snake.front().second] = PLAYER;
	for (int i = 0; i < _board.size(); i++) {
		_board[0][i] = UNWALKABLE;
		_board[_board.size() - 1][i] = UNWALKABLE;
	}
	for (int i = 0; i < _board[0].size(); i++) {
		_board[i][0] = UNWALKABLE;
		_board[i][_board[0].size() - 1] = UNWALKABLE;
	}
}

Snake::~Snake()
{
}

void Snake::left()
{
	if (_face == UP || _face == DOWN) {
		_face = LEFT;
	}
}

void Snake::right()
{
	if (_face == UP || _face == DOWN) {
		_face = RIGHT;
	}
}

void Snake::up()
{
	if (_face == LEFT || _face == RIGHT) {
		_face = UP;
	}
}

void Snake::down()
{
	if (_face == LEFT || _face == RIGHT) {
		_face = DOWN;
	}
}

void Snake::action()
{
}

void Snake::update()
{
	if (!_gameOver && _tik == 3) {
		if (_face == UP) {
			_snake.push(*new std::pair<int, int>(_snake.back().first -1, _snake.back().second));
		}
		if (_face == DOWN) {
			_snake.push(*new std::pair<int, int>(_snake.back().first+1, _snake.back().second));
		}
		if (_face == LEFT) {
			_snake.push(*new std::pair<int, int>(_snake.back().first, _snake.back().second-1));
		}
		if (_face == RIGHT) {
			_snake.push(*new std::pair<int, int>(_snake.back().first, _snake.back().second+1));
		}
		if (_board[_snake.back().first][_snake.back().second] == WALKABLE) {
			_board[_snake.front().first][_snake.front().second] = WALKABLE;
			_snake.pop();
			_board[_snake.back().first][_snake.back().second] = PLAYER;
		} else if (_board[_snake.back().first][_snake.back().second] == EAT) {
			_board[_snake.back().first][_snake.back().second] = PLAYER;
			new_pellet();
			_score += 10;
		} else {
			_score = -1;
			_gameOver = true;
		}
		_tik = 0;
	} else if (!_gameOver)
		_tik++;
	
}

void Snake::new_pellet()
{
	bool found = false;
	int x;
	int y;

	while (!found) {
		x = rand()%_board.size();
		y = rand()%_board[0].size();
		if (_board[x][y] == WALKABLE) {
			_board[x][y] = EAT;
			found = true;
		}
	}
}