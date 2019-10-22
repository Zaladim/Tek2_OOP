/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** AGame Abstract
*/

#include "AGame.hpp"
#include <iostream>

AGame::AGame() : 
	_score(0)
{
	setBoard(50, 50);
}

AGame::~AGame()
{
}

// === GETTER ===
std::vector<std::vector<int>> &AGame::getBoard()
{
	return _board;
}

int AGame::getPos(int x, int y)
{
	if (x > _board.size() || y > _board[0].size() || x < 0 || y < 0)
		return (-1);
	return (_board[x][y]);
}

int AGame::getScore()
{
	return (_score);
}

// === SETTER ===
void AGame::setBoard(int x, int y)
{
	std::vector<std::vector<int>> ret;
	for(int i = 0; i < x; i++) {
		std::vector<int> tmp;
		for(int j = 0; j < y; j++) {
			tmp.push_back(WALKABLE);
		}
		ret.push_back(tmp);
	}
	_board = ret;
}

void AGame::setPos(int x, int y, int val)
{
	if (x < _board.size() && y < _board[0].size() && x >= 0 && y >= 0)
		_board[x][y] = val;
}