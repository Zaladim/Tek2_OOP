/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Soft wall
*/

#include "Soft.hpp"

Soft::Soft(int x, int y, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector) :
AEntity(x, y, SOFT)
{
    _3dModel = scene->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df((irr::f32)x*10, (irr::f32)y*10, 20.0f));
    _3dModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _3dModel->setMaterialTexture(0, driver->getTexture(getTexture("crate03.jpg").c_str()));
    selector = scene->createTriangleSelectorFromBoundingBox(_3dModel);
    _3dModel->setTriangleSelector(selector);
    metaSelector->addTriangleSelector(selector);
    _anim = scene->createCollisionResponseAnimator(metaSelector, _3dModel, irr::core::vector3df(2, 2, 1), irr::core::vector3df(0.0f, 0.0f, 0.0f));
    _3dModel->addAnimator(_anim);
    _meta = metaSelector;
    _scene = scene;
    _driver = driver;
}

Soft::~Soft()
{
    _meta->removeTriangleSelector(selector);
    _3dModel->remove();
    selector->drop();
}

AEntity *Soft::destroy()
{
	int val = std::rand() % 100;
	if (val > 70) {
		if (val > 90)
			return new PowerUp(_x, _y, FIREUP, _scene, _driver);
		if (val > 80)
			return new PowerUp(_x, _y, SPEEDUP, _scene, _driver);
        if (val > 70)
		    return new PowerUp(_x, _y, BOMBUP, _scene, _driver);
	}
	return new Floor(_x, _y);
}