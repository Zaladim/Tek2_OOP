/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Procedural level generation
*/

#ifndef BOARDGENERATOR_HPP_
#define BOARDGENERATOR_HPP_

#include <vector>
#include <cstdlib>
#include <ctime>
#include "AEntity.hpp"

class BoardGenerator {
	public:
		BoardGenerator(int x, int y);
		~BoardGenerator() = default;

		std::vector<std::vector<int>> generate(int wall, int soft);

	protected:
	private:
		bool checkPoint(int i, int j, std::vector<std::vector<int>> board);
		bool check(std::vector<std::vector<int>> board);
		int _x;
		int _y;
};

#endif /* !BOARDGENERATOR_HPP_ */
