/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** game board
*/

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <memory>
#include "AEntity.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "BoardGenerator.hpp"
#include "Wall.hpp"
#include "Soft.hpp"
#include "PowerUp.hpp"
#include "Floor.hpp"
#include "Bomb.hpp"
#include "Timer.hpp"

#define MAXX 13
#define MAXY 11

class Board {
	public:
		Board(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, int players = 1);
		// Board(const BoardGenerator &gen, \
		// 	const std::vector<std::vector<std::unique_ptr<AEntity>>> &entities, \
		// 	const std::vector<std::unique_ptr<AEntity>> &players, \
		// 	const std::vector<std::unique_ptr<AEntity>> &monsters, \
		// 	const std::vector<std::unique_ptr<AEntity>> &bombs);
		~Board();

		int getX() const;
		int getY() const;
		AEntity *getPos(int x, int y);
		bool checkBomb(int x, int y);

		void setPos(int x, int y, AEntity *);

		int update();
		void newEntity(std::unique_ptr<AEntity> entity);
		void newPlayer();

		AEntity &operator()(int x, int y);
		std::vector<std::unique_ptr<AEntity>> _bombs;
		std::vector<std::unique_ptr<AEntity>> _players;
		std::vector<std::unique_ptr<AEntity>> _monsters;

	private:
		int explode(int x, int y, int power);
		const int _x = MAXX;
		const int _y = MAXY;


		std::vector<std::vector<std::unique_ptr<AEntity>>> _entities; // List of every existing entities
		// std::vector<std::vector<int>> _floor; //Floor tiles, important on certain levels

		BoardGenerator _gen;

};

#endif /* !BOARD_HPP_ */