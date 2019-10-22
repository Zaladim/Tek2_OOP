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
		Player(int, int, irr::scene::ISceneManager *,irr::video::IVideoDriver *, irr::f32, irr::s32, int, irr::core::vector3df, irr::scene::IMetaTriangleSelector *metaSelector, int score = 0, int id = -1);
		~Player();

		int getId() const;
		float getSpeed() const;
		int getBomb() const;
		int getMaxBomb() const;
		int getScore() const;
		bool getwallPass() const;

		void reset();

		std::unique_ptr<Bomb> bomb(irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver);
		void move(irr::core::vector3df) override;
        irr::scene::IAnimatedMeshSceneNode *_3dModel;	
		void addBomb();
		void addPower(power_type type);
		void addScore(int score);

		void setNode(float x, float y, std::vector<std::unique_ptr<AEntity>> &bombs) override;
		void setDirection(direction_t direction);

	private:
		static int cpt;
		int _id;

		int _score;
		int _startX;
		int _startY;

		int _power = 1;
		int _bomb = 1;
		int _bombMax = 2;
		float _speed = 30.0f;
		bool _wallPass = false;
        irr::scene::ITriangleSelector* selector;
        irr::scene::ISceneNodeAnimatorCollisionResponse* _anim;
		irr::scene::IMetaTriangleSelector *_metaSelector;
};

#endif /* !PLAYER_HPP_ */