/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Power up
*/

#include "PowerUp.hpp"

PowerUp::PowerUp(int x, int y, power_type type, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver) :
	AEntity(x, y, POWER_UP),
	_type(type)
{
    _3dModel = scene->addSphereSceneNode(2.5f, 32, 0, -1, irr::core::vector3df((irr::f32)x * 10, (irr::f32)y * 10, 20.0f));
    _3dModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    switch (type)
    {
    case power_type::BOMBUP:
        _3dModel->setMaterialTexture(0, driver->getTexture(getTexture("ornam03.jpg").c_str()));        
        break;
    case power_type::FIREUP:
        _3dModel->setMaterialTexture(0, driver->getTexture(getTexture("ornam13.jpg").c_str()));        
        break;
    case power_type::SPEEDUP:
        _3dModel->setMaterialTexture(0, driver->getTexture(getTexture("pastel07r.jpg").c_str()));        
        break;
    case power_type::WALLUP :
        _3dModel->setMaterialTexture(0, driver->getTexture(getTexture("brick006b.jpg").c_str()));        
        break;
    default:
        break;
    }
}

PowerUp::~PowerUp()
{
    _3dModel->remove();
}

AEntity *PowerUp::destroy()
{

	_exist = false;
	return new Floor(_x, _y);
}

power_type PowerUp::getType() const
{
	return _type;
}