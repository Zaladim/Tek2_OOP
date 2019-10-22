/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Wall
*/

#include "Wall.hpp"

Wall::Wall(int x, int y, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver, irr::scene::IMetaTriangleSelector *metaSelector) :
AEntity(x, y, WALL)
{
	_3dModel = scene->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df((irr::f32)x*10, (irr::f32)y*10, 20.0f));
    _3dModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _3dModel->setMaterialTexture(0, driver->getTexture(getTexture("brick077.jpg").c_str()));
    selector = scene->createTriangleSelectorFromBoundingBox(_3dModel);
    _3dModel->setTriangleSelector(selector);
    metaSelector->addTriangleSelector(selector);
    _anim = scene->createCollisionResponseAnimator(metaSelector, _3dModel, irr::core::vector3df(2, 2, 1), irr::core::vector3df(0.0f, 0.0f, 0.0f));
    _3dModel->addAnimator(_anim);
    _meta = metaSelector;
    _scene = scene;
    _driver = driver;
}

Wall::~Wall()
{
	_meta->removeTriangleSelector(selector);
    _3dModel->remove();
    selector->drop();
}