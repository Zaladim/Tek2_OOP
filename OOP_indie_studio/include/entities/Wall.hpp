/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Wall
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "AEntity.hpp"
#include "Floor.hpp"

class Wall : public AEntity {
	public:
		Wall(int x, int y, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector);
		~Wall();


	protected:
	private:
		irr::scene::IMeshSceneNode *_3dModel;
        irr::scene::ISceneManager *_scene;
        irr::video::IVideoDriver *_driver;
        irr::scene::ITriangleSelector* selector;
        irr::scene::ISceneNodeAnimatorCollisionResponse* _anim;
        irr::scene::IMetaTriangleSelector *_meta;
};

#endif /* !WALL_HPP_ */
