/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Mobs
*/

#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <cstdlib>
#include <ctime>
#include "AEntity.hpp"
#include "AMovable.hpp"

class Monster : public AEntity, AMovable {
	public:
		Monster(int, int, irr::scene::ISceneManager *,irr::video::IVideoDriver *, irr::core::vector3df);
		~Monster();

		void move(irr::core::vector3df) override;

		void move(irr::f32 frame, AEntity &, AEntity &, AEntity &, AEntity &);

		void setNode(float x, float y);

	protected:
	private:
		int _tik = 10;
		bool _changeDir = false;
		irr::scene::IMeshSceneNode *_3dModel;	
};

#endif /* !MONSTER_HPP_ */
