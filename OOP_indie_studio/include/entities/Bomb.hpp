/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Bomb object
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "ATimed.hpp"
#include "Floor.hpp"
#include "Timer.hpp"

class Bomb : public ATimed {
	public:
		Bomb(int x, int y, int power, int playerId, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector);
		~Bomb() override;

		int getPower() const;
		int getId() const;
		bool colliding() const;
		AEntity *destroy() override;

		void setCollision(irr::scene::ISceneManager &scene);

	private:
		bool collide = false;
		int _power;
		int _playerId;
        irr::scene::IMeshSceneNode *_3dModel;
		irr::scene::ITriangleSelector* selector;
        irr::scene::ISceneNodeAnimatorCollisionResponse* _anim;
		irr::scene::IMetaTriangleSelector *_metaSelector;
};

#endif /* !BOMB_HPP_ */
