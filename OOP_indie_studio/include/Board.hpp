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
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>
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
#include "Sound.hpp"
#include "Explosion.hpp"

#define MAXX 13
#define MAXY 11

class Board {
	public:
		Board(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector, Sound &soundBox, int players = 1);
		Board(std::string save, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector, Sound &soundBox);
		~Board();

		int getX() const;
		int getY() const;
		AEntity *getPos(int x, int y);
		std::vector<std::unique_ptr<AEntity>> &getPlayers() {return _players;}
		std::vector<std::unique_ptr<AEntity>> &getBombs() {return _bombs;}
		std::vector<std::unique_ptr<AEntity>> &getMonsters() {return _monsters;}
		int getLevel() const;
		void setLevel(int level);

		bool checkBomb(int x, int y);
		bool checkMonster(int x, int y);

		void setPos(int x, int y, AEntity *);

		void newLevel(int level, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector);
		void death();
		boost::filesystem::path saveGame(std::string save);

		int update(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver);
		void newEntity(std::unique_ptr<AEntity> entity);
		void newPlayer();
		void generateMonsters(int nb, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver);
		void clearAll();
		AEntity &operator()(int x, int y);
		int _playerCounted;

	private:
		int explode(int x, int y, int power, int id, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver);
		const int _x = MAXX;
		const int _y = MAXY;
		int _level = 1;

		std::vector<std::unique_ptr<AEntity>> _bombs;
		std::vector<std::unique_ptr<AEntity>> _players;
		std::vector<std::unique_ptr<AEntity>> _monsters;

		std::vector<std::vector<std::unique_ptr<AEntity>>> _entities; // List of every existing entities
		std::vector<std::unique_ptr<Explosion>> _explosion;

		BoardGenerator _gen;
		Sound &_soundBox;

};

#endif /* !BOARD_HPP_ */