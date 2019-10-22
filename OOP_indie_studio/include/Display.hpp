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
#include "Player.hpp"
#include "Sound.hpp"
#include "Directories.hpp"

#define NORMAL 0
#define NEWLEVEL 1

typedef enum state {
    START_MENU,
    PAUSE,
    START_GAME,
    SAVE,
    GAME,
    DEATH,
    CREDIT
} state_t;

class Display {
	public:
		Display();
		~Display();

		void setOpt();
		void setElem(Board &board);
		void setCam();
        void setPlayers(int players);

        bool checkWalkable(Board &board, int x, int y, AEntity *player);

		bool isRunning();
        int displayStartMenu();
        int displayPause();
        int displayCredit();
        int displaySave(Board &board);
		int displayAll(Board &board);
        state_t getState() const;
        int getPlayers() const;
        int getNbSave() const;
        std::string getSaves(int nb) const;
        void setState(state_t state);
        void add_save(boost::filesystem::path p);
        irr::video::IVideoDriver *getDriver() {return _driver;}
        irr::scene::ISceneManager *getScene() {return _sceneManager;}
        irr::scene::IMetaTriangleSelector *getMeta() {return _metaSelector;}
        void displayLittleMessage(std::wstring title, std::wstring message);
	protected:
	private:

    irr::gui::IGUIStaticText *displayInfo(Player *player, Board &board, int x, \
        int x2, int nb);

    Sound _soundBox;

    MyEventReceiver _event;
    irr::IrrlichtDevice *_device;
    irr::video::IVideoDriver *_driver;
    irr::scene::ISceneManager *_sceneManager;
    irr::gui::IGUIEnvironment *_gui;
    state_t _state;

    irr::gui::IGUIButton *_bouton_play;
    irr::gui::IGUIButton *_bouton_continue;
    irr::gui::IGUIButton *_bouton_return_back;
    irr::gui::IGUIButton *_bouton_save;
    irr::gui::IGUIComboBox *_box_player;
    irr::gui::IGUIComboBox *_box_saves;

    irr::gui::IGUIEditBox *_savename_editBox;

    std::vector<irr::scene::IMeshSceneNode *> _floor;
    std::vector<irr::scene::IMeshSceneNode *> _soft;
    irr::scene::IMeshSceneNode *_sphere;
	irr::u32 _then;
    irr::f32 _movSpeed;
    irr::u32 _now;
    irr::f32 _frameDeltaTime;
    irr::scene::ITriangleSelector* _selector;
    irr::scene::IMetaTriangleSelector* _metaSelector;
    irr::scene::ISceneNodeAnimatorCollisionResponse *_anim;
    irr::core::vector3df _tmp;
    bool _running = true;
    bool _pause = false;
    int _players = 1;
    int _nbsave = 0;
    std::vector<std::string> _saves;
};

#endif /* !DISPLAY_HPP_ */
