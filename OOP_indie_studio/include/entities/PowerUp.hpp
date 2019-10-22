/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Power up
*/

#ifndef PowerUp_HPP_
#define PowerUp_HPP_

#include "AEntity.hpp"
#include "Floor.hpp"

enum power_type {
	BOMBUP,
	FIREUP,
	SPEEDUP,
	WALLUP
};

class PowerUp : public AEntity {
	public:
		PowerUp(int x, int y, power_type type, irr::scene::ISceneManager *scene, irr::video::IVideoDriver *driver);
		~PowerUp();
        power_type getType() const;
        AEntity *destroy() override;

    protected:
        power_type _type;
    private:
        irr::scene::IMeshSceneNode *_3dModel;
};

#endif /* !PowerUp_HPP_ */
