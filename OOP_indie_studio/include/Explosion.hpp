/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Explosion
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include <irrlicht/irrlicht.h>
#include "Directories.hpp"
#include "Timer.hpp"

class Explosion {
	public:
		Explosion(irr::f32 x, irr::f32 y, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver);
		~Explosion();

		int update();

	protected:
	private:
		irr::scene::IMeshSceneNode *_3dModel;
		Timer _t;
};

#endif /* !EXPLOSION_HPP_ */
