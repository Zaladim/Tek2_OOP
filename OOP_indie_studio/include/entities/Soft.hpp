/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Soft wall
*/

#ifndef SOFT_HPP_
#define SOFT_HPP_

#include <cstdlib>
#include <ctime>
#include "AEntity.hpp"
#include "Floor.hpp"
#include "PowerUp.hpp"

class Soft : public AEntity {
	public:
		Soft(int x, int y, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector);
		~Soft();

		AEntity *destroy() override;
	private:
        irr::scene::IMeshSceneNode *_3dModel;
        irr::scene::ISceneManager *_scene;
        irr::video::IVideoDriver *_driver;
        irr::scene::ITriangleSelector* selector;
        irr::scene::ISceneNodeAnimatorCollisionResponse* _anim;
        irr::scene::IMetaTriangleSelector *_meta;
};

#endif /* !SOFT_HPP_ */
