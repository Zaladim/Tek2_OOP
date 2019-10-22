/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Procedural level generation
*/

#include "BoardGenerator.hpp"
BoardGenerator::BoardGenerator(int x, int y) :
	_x(x),
	_y(y)
{
}

std::vector<std::vector<int>> BoardGenerator::generate(int wall, int soft)
{
	std::vector<std::vector<int>> board;

	for (int i = 0; i < _x; i++) {
		std::vector<int> tmp;
		for (int j = 0; j < _y; j++) {
			if (i%2 == 1 && j%2 == 1) {
				tmp.push_back(WALL);
			} else {
				tmp.push_back(FLOOR);
			}
		}
		board.push_back(tmp);
	}

	board[0][0] = START;
	board[0][1] = START;
	board[1][0] = START;
	board[_x - 1][0] = START;
	board[_x - 1][1] = START;
	board[_x - 2][0] = START;
	board[0][_y - 1] = START;
	board[0][_y - 2] = START;
	board[1][_y - 1] = START;
	board[_x - 1][_y - 1] = START;
	board[_x - 1][_y - 2] = START;
	board[_x - 2][_y - 1] = START;

	srand(time(NULL));
	while (wall > 0) {
		for (int i = 0; i < _x; i++) {
			for (int j = 0; j < _y; j++) {
				if (wall <= 0)
					break;
				if (checkPoint(i, j, board)) {
					board[i][j] = WALL;
					wall--;
				}
			}
		}
	}

	while (soft > 0) {
		for (int i = 0; i < _x; i++) {
			for (int j = 0; j < _y; j++) {
				if (soft <= 0)
					return board;
				if (board[i][j] == FLOOR && rand()%20 == 1) {
					board[i][j] = SOFT;
					soft--;
				}
			}
		}
	}

	return board;
}

bool BoardGenerator::checkPoint(int i, int j, std::vector<std::vector<int>> board)
{
	int ways = 0;

	if (((i%2 == 0 && j%2 == 1) || (i%2 == 1 && j%2 == 0)) &&rand()%10 == 1) {
		if (i < _x - 1 && board[i+1][j] == FLOOR)
			ways++;
		if (i > 0 && board[i-1][j] == FLOOR)
			ways++;
		if (j < _y - 1 && board[i][j+1] == FLOOR)
			ways++;
		if (j > 0 && board[i][j-1] == FLOOR)
			ways++;
		if (ways >= 2)
			return true;
	}
	return false;
}

bool BoardGenerator::check(std::vector<std::vector<int>> board)
{
	int x = 0;
	int y = 0;

	for (int i = 0; i < _x; i++) {
		
	}
	return true;
}