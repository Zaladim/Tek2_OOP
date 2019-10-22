/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Explosion
*/

#include "Explosion.hpp"

Explosion::Explosion(irr::f32 x, irr::f32 y, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver)
{
	_3dModel = scene->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df((irr::f32)x*10, (irr::f32)y*10, 20.0f));
    _3dModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _3dModel->setMaterialTexture(0, driver->getTexture(getTexture("fire.jpg").c_str()));
}

Explosion::~Explosion()
{
	_3dModel->remove();
}

int Explosion::update() {
	if (_t.getElapsedTime() >= 500) {
		return 0;
	}
	return -1;
}
