/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** game board
*/

#include "bomberman.hpp"
#include "Board.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include "Bomb.hpp"
#include "Display.hpp"

Display::Display() :
    _event(),
    _device(irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1000,1000), 32, false, false, false, &_event)),
    _driver(_device->getVideoDriver()),
    _sceneManager(_device->getSceneManager()),
    _then(_device->getTimer()->getTime()),
    _movSpeed(30.0f)
    // _nodePosition(irr::core::vector3df(0.0f, 0.0f, 20.0f))
    //_player(0, 0, _sceneManager, _driver, 5.0f, 32, -1, irr::core::vector3df(0.0f, 0.0f, -20.0f))
{
}

Display::~Display()
{
    _device->drop ();
}

void Display::setOpt()
{
    _device->getCursorControl ()-> setVisible (false);
    _device->setWindowCaption(L"Bomberman");
}

void Display::setElem(Board &board)
{
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 11; j++) {
            if (board(i, j) == WALL)
                _cube.push_back(_sceneManager->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df((irr::f32)(i*10), (irr::f32)(j*10), 20.0f)));
        }
    }
    for (size_t i = 0; i < _cube.size(); i++) {
        _cube.at(i)->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _cube.at(i)->setMaterialTexture(0, _driver->getTexture("assets/brick002.jpg")); 
    }
}

void Display::setCam()
{
    _sceneManager->addCameraSceneNode(0, core::vector3df(55, 10, -120),core::vector3df(55, 45, 0));
}

void Display::setPlayers(int players) {
    _players = players;
}

bool Display::isRunning()
{
    if (!_running)
        return false;
    return(_device->run());
}

void Display::displayAll(Board &board)
{
    irr::video::SColor color(255, 255, 255, 255);

    _now = _device->getTimer()->getTime();
    _frameDeltaTime = (irr::f32)(_now - _then) / 1000.f;
    _then = _now;

    if (_event.IsKeyDown(irr::KEY_KEY_Z) && _colision.checkcolision(board._players[0], 0, _frameDeltaTime, board)) {
        // dynamic_cast<Player *>(board._players[0].get())->move(board._players[0]->getNode());
        board._players[0]->setNode(0, _frameDeltaTime);
    }
    if (_event.IsKeyDown(irr::KEY_KEY_S) && _colision.checkcolision(board._players[0], 0, -_frameDeltaTime, board)) {
        //dynamic_cast<Player *>(board._players[0].get())->move(_nodePosition);
        board._players[0]->setNode(0, - _frameDeltaTime);
    }
    if (_event.IsKeyDown(irr::KEY_KEY_Q) && _colision.checkcolision(board._players[0], -_frameDeltaTime, 0, board)) {
        //dynamic_cast<Player *>(board._players[0].get())->move(_nodePosition);
        board._players[0]->setNode(-_frameDeltaTime, 0);
    }
    if (_event.IsKeyDown(irr::KEY_KEY_D) && _colision.checkcolision(board._players[0], _frameDeltaTime, 0, board)) {
        //dynamic_cast<Player *>(board._players[0].get())->move(_nodePosition);
        board._players[0]->setNode(_frameDeltaTime, 0);
    }
    if (_event.IsKeyDown(irr::KEY_SPACE) && !board.checkBomb(board._players[0]->getX(), board._players[0]->getY())) {
        std::unique_ptr<AEntity> tmp = dynamic_cast<Player *>(board._players[0].get())->bomb(_sceneManager, _driver);
        if (tmp.get())
            board.newEntity(std::move(tmp));
    }
    dynamic_cast<Player *>(board._players[0].get())->_3dModel->setPosition(dynamic_cast<Player *>(board._players[0].get())->getNode());


    // TWO PLAYERS
    if (_players > 1) {


        if (_event.IsKeyDown(irr::KEY_UP) && _colision.checkcolision(board._players[1], 0, _frameDeltaTime, board)) {
            // dynamic_cast<Player *>(board._players[0].get())->move(board._players[0]->getNode());
            board._players[1]->setNode(0, _frameDeltaTime);
        }
        if (_event.IsKeyDown(irr::KEY_DOWN) && _colision.checkcolision(board._players[1], 0, -_frameDeltaTime, board)) {
            //dynamic_cast<Player *>(board._players[0].get())->move(_nodePosition);
            board._players[1]->setNode(0, - _frameDeltaTime);
        }
        if (_event.IsKeyDown(irr::KEY_LEFT) && _colision.checkcolision(board._players[1], -_frameDeltaTime, 0, board)) {
            //dynamic_cast<Player *>(board._players[0].get())->move(_nodePosition);
            board._players[1]->setNode(-_frameDeltaTime, 0);
        }
        if (_event.IsKeyDown(irr::KEY_RIGHT) && _colision.checkcolision(board._players[1], _frameDeltaTime, 0, board)) {
            //dynamic_cast<Player *>(board._players[0].get())->move(_nodePosition);
            board._players[1]->setNode(_frameDeltaTime, 0);
        }
        if (_event.IsKeyDown(irr::KEY_RETURN)) {
            std::unique_ptr<AEntity> tmp = dynamic_cast<Player *>(board._players[1].get())->bomb(_sceneManager, _driver);
            if (tmp.get())
                board.newEntity(std::move(tmp));
        }
        dynamic_cast<Player *>(board._players[1].get())->_3dModel->setPosition(dynamic_cast<Player *>(board._players[1].get())->getNode());

    }

    for (auto &m : board._monsters) {
        dynamic_cast<Monster *>(m.get())->move(_frameDeltaTime, board(m->getX() + 1, m->getY()), board(m->getX() - 1, m->getY()), board(m->getX(), m->getY() + 1), board(m->getX(), m->getY() - 1));
    }


    // std::cout<<"X: "<< _nodePosition.X<<std::endl;
    // std::cout<<"Y :"<< _nodePosition.Y<<std::endl;

    if (board.update()) {
        std::cout << "GAME OVER" << std::endl;
        _running = false;
    }

    _driver->beginScene(true, true, color); 
    _sceneManager->drawAll();
    _driver->endScene();
}