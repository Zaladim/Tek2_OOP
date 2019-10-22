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
    _gui(_sceneManager->getGUIEnvironment()),
    _state(START_MENU),
    _then(_device->getTimer()->getTime()),
    _movSpeed(30.0f)
{
    for (int i = 0; i < MAXX; i++) {
        for (int j = 0; j < MAXY; j++) {
            irr::scene::IMeshSceneNode *cube = _sceneManager->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df((irr::f32)i * 10, (irr::f32)j * 10, 30.0f));
            cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            cube->setMaterialTexture(0, _driver->getTexture(getTexture("veg011.jpg").c_str()));
            _floor.push_back(cube);
        }
    }
    _savename_editBox = _gui->addEditBox(L"Default", irr::core::rect<irr::s32>(400,500,600,520));

    _bouton_play = _gui->addButton(irr::core::rect<irr::s32>(430,600,570,630), 0, -1);
    _bouton_play->setDrawBorder(false);
    _bouton_continue = _gui->addButton(irr::core::rect<irr::s32>(250,400,350,450), 0, -1, L"continue");
    _bouton_save = _gui->addButton(irr::core::rect<irr::s32>(450,400,550,450), 0, -1, L"save");
    _bouton_return_back = _gui->addButton(irr::core::rect<irr::s32>(650,400,750,450), 0, -1, L"quit");

    _box_player = _gui->addComboBox(irr::core::rect<irr::s32>(430,675,570,700));
    _box_player->addItem(L"1 joueur");
    _box_player->addItem(L"2 joueurs");
    _box_saves = _gui->addComboBox(irr::core::rect<irr::s32>(430,725,570,750));
    _box_saves->addItem(L"New game");
    read_directory("save", _saves);
    for (auto s : _saves) {
        _box_saves->addItem(std::wstring(s.begin(), s.end()).c_str());
    }
}

void Display::add_save(boost::filesystem::path p)
{
    std::string str = p.c_str();
    _box_saves->addItem(std::wstring(str.begin(), str.end()).c_str());
    _saves.push_back(std::string(str.begin(), str.end()));
}

Display::~Display()
{
    for (auto &elem : _floor) {
        elem->remove();
    }
    _floor.clear();
    _device->drop ();
}

void Display::setOpt()
{
    _device->getCursorControl ()-> setVisible (false);
    _device->setWindowCaption(L"Bomberman");
}

void Display::displayLittleMessage(std::wstring title, std::wstring message)
{
    _gui->addMessageBox(title.c_str(), message.c_str(), true, irr::gui::EMBF_OK);
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

state_t Display::getState() const
{
    return (_state);
}

void Display::setState(state_t state)
{
    _state = state;
}

int Display::getPlayers() const
{
    return (_players);
}

std::string Display::getSaves(int nb) const
{
    if (_saves.size() > nb - 1 && nb - 1 >= 0)
        return (_saves[nb - 1]);
    return ("Wrong");
}

int Display::getNbSave() const
{
    return (_nbsave);
}

int Display::displayStartMenu()
{
    _driver->beginScene(true, true, irr::video::SColor(0,0,0,0));
    _metaSelector = _sceneManager->createMetaTriangleSelector();

    irr::video::ITexture *image = _driver->getTexture(getTexture("bomb_atomic.jpg").c_str());
    _driver->draw2DImage(image, irr::core::position2d<irr::s32>(0,100),
        irr::core::rect<irr::s32>(0,0,1600,771), 0,
        irr::video::SColor(255, 255, 255, 255), true);
    image = _driver->getTexture(getTexture("title.png").c_str());
    _driver->draw2DImage(image, irr::core::position2d<irr::s32>(200,300),
        irr::core::rect<irr::s32>(0,0,600,290), 0,
        irr::video::SColor(255, 255, 255, 255), true);
    image = _driver->getTexture(getTexture("playnow.png").c_str());
    _driver->draw2DImage(image, irr::core::position2d<irr::s32>(430,600),
        irr::core::rect<irr::s32>(60,115,200,145), 0,
        irr::video::SColor(255, 255, 255, 255), true);

    _bouton_play->setVisible(true);
    _box_player->setVisible(true);
    _box_saves->setVisible(true);
    _bouton_continue->setVisible(false);
    _bouton_return_back->setVisible(false);
    _bouton_save->setVisible(false);
    _savename_editBox->setVisible(false);

    _gui->drawAll();

    _driver->endScene();
    _device->getCursorControl ()-> setVisible(true);
    _device->setWindowCaption(L"Bomberman");
    if (_bouton_play->isPressed()) {
        _soundBox.play(CLICK);
        _players = _box_player->getSelected() + 1;
        _nbsave = _box_saves->getSelected();
        _state = START_GAME;
    }
    _now = _device->getTimer()->getTime();
    _then = _now;
    return NORMAL;
}

int Display::displayCredit()
{
    _driver->beginScene(true, true, irr::video::SColor(255,255,255,255));
    
    irr::video::ITexture *image = _driver->getTexture(getTexture("papier-peint-nuages-cartoon.jpg").c_str());
    _driver->draw2DImage(image, irr::core::position2d<irr::s32>(0,0),
        irr::core::rect<irr::s32>(0,0,1000,1000), 0,
        irr::video::SColor(255, 255, 255, 255), true);

    _bouton_play->setVisible(false);
    _box_player->setVisible(false);
    _box_saves->setVisible(false);
    _bouton_continue->setVisible(false);
    _bouton_return_back->setVisible(false);
    _bouton_save->setVisible(false);
    _savename_editBox->setVisible(false);

   
    _device->getCursorControl ()-> setVisible(true);
    _device->setWindowCaption(L"Bomberman");

    irr::gui::IGUIStaticText *texte = _gui->addStaticText(L"        BOMBERMAN!\n\nby: Charles, Adrien, Paul, Pierre, Francois, Martin",
    irr::core::rect<irr::s32>(210,300,810,500), true, true, 0, -1, true);
    irr::gui::IGUIFont *font = _gui->getFont(getFont("bigfont.png").c_str());
    texte->setOverrideFont(font);
    texte->setDrawBackground(false);
    texte->setDrawBorder(false);
    _gui->drawAll();
     _driver->endScene();
    sleep(4);
    texte->remove();
    
    _state = START_MENU;
    return NORMAL;

}

int Display::displayPause()
{
    _driver->beginScene(true, true, irr::video::SColor(0,0,0,0));

    irr::video::ITexture *image = _driver->getTexture(getTexture("pause_back_ground.jpg").c_str());
    _driver->draw2DImage(image, irr::core::position2d<irr::s32>(0,140),
        irr::core::rect<irr::s32>(200,0,1200,720), 0,
        irr::video::SColor(255, 255, 255, 255), true);
    
    _bouton_play->setVisible(false);
    _box_player->setVisible(false);
    _box_saves->setVisible(false);
    _bouton_continue->setVisible(true);
    _bouton_return_back->setVisible(true);
    _bouton_save->setVisible(true);
    _savename_editBox->setVisible(false);

    _bouton_return_back->setText(L"quit");
    _bouton_continue->setText(L"continue");;
    _gui->drawAll();

    _driver->endScene();
    _device->getCursorControl ()-> setVisible(true);
    _device->setWindowCaption(L"Bomberman Pause");

    if (_event.IsKeyDown(irr::KEY_ESCAPE) || _bouton_continue->isPressed()) {
        _soundBox.play(CLICK);
        _state = GAME;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } else if (_bouton_return_back->isPressed()) {
        _soundBox.play(CLICK);
        _state = START_MENU;
    } else if (_bouton_save->isPressed()) {
        _soundBox.play(CLICK);
        _state = SAVE;  
    }
    _now = _device->getTimer()->getTime();
    _then = _now;
    return NORMAL;
}

int Display::displaySave(Board &board)
{

    _driver->beginScene(true, true, irr::video::SColor(0,0,0,0));

    irr::video::ITexture *image = _driver->getTexture(getTexture("pause_back_ground.jpg").c_str());
    _driver->draw2DImage(image, irr::core::position2d<irr::s32>(0,140),
        irr::core::rect<irr::s32>(200,0,1200,720), 0,
        irr::video::SColor(255, 255, 255, 255), true);

    _bouton_play->setVisible(false);
    _box_player->setVisible(false);
    _box_saves->setVisible(false);
    _bouton_continue->setVisible(true);
    _bouton_return_back->setVisible(true);
    _bouton_save->setVisible(false);
    _savename_editBox->setVisible(true);

    _bouton_return_back->setText(L"Go back");
    _bouton_continue->setText(L"Save");
    _gui->drawAll();
    _driver->endScene();
    _device->getCursorControl()->setVisible(true);
    _device->setWindowCaption(L"Bomberman Save Menu");

    if (_event.IsKeyDown(irr::KEY_ESCAPE) || _bouton_return_back->isPressed()) {
        _soundBox.play(CLICK);
        _state = PAUSE;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } else if (_bouton_continue->isPressed()) {
        _soundBox.play(CLICK);
        std::wstring ws(_savename_editBox->getText());
        std::string str(ws.begin(), ws.end());
        add_save(board.saveGame(str + ".txt"));
        _gui->addMessageBox(L"Successfull save", L"c'est cool.", true, irr::gui::EMBF_OK);
    }
    return NORMAL;
}

bool Display::checkWalkable(Board &board, int x, int y, AEntity *player) {
    if (x == player->getX() && y == player->getY()) {
        return true;
    }
    
    if (x < 0 || y < 0 || x >= MAXX || y >= MAXY) {
        return false;
    }
    AEntity tmp = board(x,y);
    if (tmp == FLOOR || tmp == POWER_UP || tmp == MONSTER) {
        return true;
    }
    return false;
}

int Display::displayAll(Board &board)
{
    _now = _device->getTimer()->getTime();
    _frameDeltaTime = (irr::f32)(_now - _then) / 1000.f;
    _then = _now;

    if (_event.IsKeyDown(irr::KEY_ESCAPE)) {
        _soundBox.play(CLICK);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        _state = PAUSE;
        return NORMAL;
    }
    irr::video::SColor color(255, 255, 255, 255);

    board.getPlayers()[0]->setNodePosition(dynamic_cast<Player *>(board.getPlayers()[0].get())->_3dModel->getPosition());

    if (_event.IsKeyDown(irr::KEY_KEY_Z)) {
        if (checkWalkable(board, board.getPlayers()[0]->getX(), board.getPlayers()[0]->getY() + _frameDeltaTime, board.getPlayers()[0].get())) {
            board.getPlayers()[0]->setNode(0, _frameDeltaTime, board.getBombs());
            dynamic_cast<Player *>(board.getPlayers()[0].get())->setDirection(UP);
        }
    }
    if (_event.IsKeyDown(irr::KEY_KEY_S)) {
        if (checkWalkable(board, board.getPlayers()[0]->getX(), board.getPlayers()[0]->getY() - _frameDeltaTime, board.getPlayers()[0].get())) {
            board.getPlayers()[0]->setNode(0, - _frameDeltaTime, board.getBombs());
            dynamic_cast<Player *>(board.getPlayers()[0].get())->setDirection(RIGHT);
        }
    }
    if (_event.IsKeyDown(irr::KEY_KEY_Q)) {
        if (checkWalkable(board, board.getPlayers()[0]->getX() - _frameDeltaTime, board.getPlayers()[0]->getY(), board.getPlayers()[0].get())) {
            board.getPlayers()[0]->setNode(-_frameDeltaTime, 0, board.getBombs());
            dynamic_cast<Player *>(board.getPlayers()[0].get())->setDirection(LEFT);
        }
    }
    if (_event.IsKeyDown(irr::KEY_KEY_D)) {
        if (checkWalkable(board, board.getPlayers()[0]->getX() + _frameDeltaTime, board.getPlayers()[0]->getY(), board.getPlayers()[0].get())) {
            board.getPlayers()[0]->setNode(_frameDeltaTime, 0, board.getBombs());
            dynamic_cast<Player *>(board.getPlayers()[0].get())->setDirection(DOWN);
        }
    }
    if (_event.IsKeyDown(irr::KEY_SPACE) && !board.checkBomb(board.getPlayers()[0]->getX(), board.getPlayers()[0]->getY())) {
        std::unique_ptr<AEntity> tmp = dynamic_cast<Player *>(board.getPlayers()[0].get())->bomb(_sceneManager, _driver);
        if (tmp.get())
            board.newEntity(std::move(tmp));
    }

    // TWO PLAYERS
    if (_players > 1) {
        board.getPlayers()[1]->setNodePosition(dynamic_cast<Player *>(board.getPlayers()[1].get())->_3dModel->getPosition());    
        if (_event.IsKeyDown(irr::KEY_UP)) {
            if (checkWalkable(board, board.getPlayers()[1]->getX(), board.getPlayers()[1]->getY() + _frameDeltaTime, board.getPlayers()[1].get())) {
                board.getPlayers()[1]->setNode(0, _frameDeltaTime, board.getBombs());
                dynamic_cast<Player *>(board.getPlayers()[1].get())->setDirection(UP);
            }
        }
        if (_event.IsKeyDown(irr::KEY_DOWN)) {
            if (checkWalkable(board, board.getPlayers()[1]->getX(), board.getPlayers()[1]->getY() - _frameDeltaTime, board.getPlayers()[1].get())) {
                board.getPlayers()[1]->setNode(0, - _frameDeltaTime, board.getBombs());
                dynamic_cast<Player *>(board.getPlayers()[1].get())->setDirection(RIGHT);
            }
        }
        if (_event.IsKeyDown(irr::KEY_LEFT)) {
            if (checkWalkable(board, board.getPlayers()[1]->getX() - _frameDeltaTime, board.getPlayers()[1]->getY(), board.getPlayers()[1].get())) {
                board.getPlayers()[1]->setNode(-_frameDeltaTime, 0, board.getBombs());
                dynamic_cast<Player *>(board.getPlayers()[1].get())->setDirection(LEFT);
            }
        }
        if (_event.IsKeyDown(irr::KEY_RIGHT)) {
            if (checkWalkable(board, board.getPlayers()[1]->getX() + _frameDeltaTime, board.getPlayers()[1]->getY(), board.getPlayers()[1].get())) {
                board.getPlayers()[1]->setNode(_frameDeltaTime, 0, board.getBombs());
                dynamic_cast<Player *>(board.getPlayers()[1].get())->setDirection(DOWN);
            }
        }
        if (_event.IsKeyDown(irr::KEY_RETURN) && !board.checkBomb(board.getPlayers()[1]->getX(), board.getPlayers()[1]->getY())) {
            std::unique_ptr<AEntity> tmp = dynamic_cast<Player *>(board.getPlayers()[1].get())->bomb(_sceneManager, _driver);
            if (tmp.get())
                board.newEntity(std::move(tmp));
        }
        dynamic_cast<Player *>(board.getPlayers()[1].get())->_3dModel->setPosition(dynamic_cast<Player *>(board.getPlayers()[1].get())->getNode());
    }

    for (auto &m : board.getMonsters()) {
        dynamic_cast<Monster *>(m.get())->move(_frameDeltaTime, board(m->getX() + 1, m->getY()), board(m->getX() - 1, m->getY()), board(m->getX(), m->getY() + 1), board(m->getX(), m->getY() - 1));
    }

    if (board.update(_sceneManager, _driver)) {
        if (_players > 1) {
            board.setLevel(board.getLevel() + 1);
            board.newLevel(board.getLevel(),_sceneManager, _driver, _metaSelector);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return NEWLEVEL;
        }
        board.setLevel(1);
        irr::gui::IGUIWindow *tmp = _gui->addMessageBox(L"Death", L"HAHA you are dead!", true, irr::gui::EMBF_OK);
        board.death();
        _state = START_MENU;
        return NORMAL;
    }
    dynamic_cast<Player *>(board.getPlayers()[0].get())->_3dModel->setPosition(dynamic_cast<Player *>(board.getPlayers()[0].get())->getNode());
    _driver->beginScene(true, true, color);

    irr::video::ITexture *image = _driver->getTexture(getTexture("papier-peint-nuages-cartoon.jpg").c_str());
    _driver->draw2DImage(image, irr::core::position2d<irr::s32>(0,0),
        irr::core::rect<irr::s32>(-(_now / 100),0,2100 - (_now / 100),1000), 0,
        irr::video::SColor(255, 255, 255, 255), true);

    std::vector<irr::gui::IGUIStaticText *> textes;

    textes.push_back(displayInfo(dynamic_cast<Player *>(board.getPlayers()[0].get()), board, 100, 200, 1));
    if (_players > 1)
        textes.push_back(displayInfo(dynamic_cast<Player *>(board.getPlayers()[1].get()), board, 200, 300, 2));

    _gui->drawAll();
    _sceneManager->drawAll();
    _driver->endScene();

    for (auto &elem : textes) {
        elem->remove();
    }
    textes.clear();

    if (board.getMonsters().empty()) {
        board.setLevel(board.getLevel() + 1);
        board.newLevel(board.getLevel(), _sceneManager, _driver, _metaSelector);
        return NEWLEVEL;
    }
    return NORMAL;
}

irr::gui::IGUIStaticText *Display::displayInfo(Player *player, Board &board, int x, int x2, int nb) {
    std::wstring tmp = L"PLAYER : " +  std::to_wstring(nb);
    tmp.append(L"\nLEVEL: " + std::to_wstring(board.getLevel()));
    tmp.append(L" \nBOMB: " + std::to_wstring(player->getBomb()));
    tmp.append(L" \nSCORE: " + std::to_wstring(player->getScore()));
    irr::gui::IGUIStaticText *texte = _gui->addStaticText(tmp.c_str(),
    irr::core::rect<irr::s32>(x,20,x2,100), true, true, 0, -1, true);
    irr::gui::IGUIFont *font = _gui->getFont(getFont("fontlucida.png").c_str());
    texte->setOverrideFont(font);
    return texte;
}