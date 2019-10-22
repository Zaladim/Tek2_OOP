/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Bomb object
*/

#include "Bomb.hpp"

Bomb::Bomb(int x, int y, int power, int playerId, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector) :
ATimed(x, y, BOMB, 3),
_power(power),
_playerId(playerId),
_metaSelector(metaSelector)
{
    _3dModel = scene->addSphereSceneNode(2.5f, 32, 0, -1, irr::core::vector3df((irr::f32)x, (irr::f32)y, 20.0f));
    _3dModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_3dModel->setMaterialTexture(0, driver->getTexture(getTexture("metal0025.jpg").c_str()));
	 selector = scene->createTriangleSelectorFromBoundingBox(_3dModel);
    _3dModel->setTriangleSelector(selector);
}

Bomb::~Bomb()
{
    _3dModel->remove();
	selector->drop();
}

int Bomb::getPower() const
{
	return _power;
}

int Bomb::getId() const
{
	return _playerId;
}

bool Bomb::colliding() const
{
	return collide;
}

void Bomb::setCollision(irr::scene::ISceneManager &scene) 
{
	collide = true;
	_metaSelector->addTriangleSelector(selector);
    _anim = scene.createCollisionResponseAnimator(_metaSelector, _3dModel, irr::core::vector3df(3, 3, 1), irr::core::vector3df(0.0f, 0.0f, 0.0f));
    _3dModel->addAnimator(_anim);
    selector->drop();
}

AEntity *Bomb::destroy() 
{
	_cpt = 0;
	return nullptr;
}
