/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** game board
*/

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>
#include "AEntity.hpp"
#include "BoardGenerator.hpp"
#include "Wall.hpp"
#include "Soft.hpp"
#include "PowerUp.hpp"
#include "Floor.hpp"
#include "bomberman.hpp"
#include "Board.hpp"
#include "Bomb.hpp"
#include "Display.hpp"
#include "MyEventReceiver.hpp"
#include "Colision.hpp"
#include "Player.hpp"
#include "Monster.hpp"

class Display {
	public:
		Display();
		~Display();

		void setOpt();
		void setElem(Board &board);
		void setCam();
        void setPlayers(int players);

		bool isRunning();
		void displayAll(Board &board);
    irr::video::IVideoDriver *getDriver() {return _driver;};
    irr::scene::ISceneManager *getScene() {return _sceneManager;}; 

	protected:
	private:

    MyEventReceiver _event;
    irr::IrrlichtDevice *_device;
    irr::video::IVideoDriver *_driver;
    irr::scene::ISceneManager *_sceneManager;
    std::vector<irr::scene::IMeshSceneNode *> _cube;
    std::vector<irr::scene::IMeshSceneNode *> _soft;
    irr::scene::IMeshSceneNode *_sphere;
	irr::u32 _then;
    irr::f32 _movSpeed;
    irr::u32 _now;
    irr::f32 _frameDeltaTime;
    Collision _colision;

    bool _running = true;
    int _players = 1;
    //Player _player;
};

#endif /* !DISPLAY_HPP_ */
