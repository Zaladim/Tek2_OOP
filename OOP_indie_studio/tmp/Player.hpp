/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "AEntity.hpp"
#include "AMovable.hpp"
#include "PowerUp.hpp"
#include "Bomb.hpp"

class Player : public AEntity, AMovable {
	public:
		Player(int, int, irr::scene::ISceneManager *,irr::video::IVideoDriver *, irr::f32, irr::s32, int, irr::core::vector3df);
		~Player();

		int getId() const;
		float getSpeed() const;

		std::unique_ptr<Bomb> bomb(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver);
		void move(irr::core::vector3df) override;
        irr::scene::IMeshSceneNode *_3dModel;		
		void addBomb();
		void addPower(power_type type);

		void setNode(float x, float y) override;

	private:
		static int cpt;
		int _id;

		int _power = 1;
		int _bomb = 2;
		int _bombMax = 2;
		bool _wallPass = false;
};

#endif /* !PLAYER_HPP_ */