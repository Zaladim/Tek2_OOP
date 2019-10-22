/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Entity abstract
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include <vector>
#include <memory>
#include <irrlicht/irrlicht.h>
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

enum entity {
	START,
	MONSTER,
	PLAYER,
	SOFT,
	POWER_UP,
	WALL,
	FLOOR,
	BOMB
};

class AEntity {
	public:
		AEntity(int x, int y, entity e, irr::core::vector3df position);
		AEntity(int x, int y, entity e);
		virtual ~AEntity();

		int getX() const;
		int getY() const;
		std::string getTexture(const char *textureName);
		irr::core::vector3df getNode() const;
		void setX(int x);
		void setY(int y);
		virtual void setNode(float x, float y, std::vector<std::unique_ptr<AEntity>> &bombs);
        virtual void setNodePosition(irr::core::vector3df pos) {_nodePosition = pos;}
		entity getEntity() const;

		virtual AEntity *destroy();
		virtual AEntity *update();

		bool operator==(const AEntity *other);
		bool operator!=(const AEntity *other);
		bool operator==(const entity e);
		bool operator!=(const entity e);
	protected:

		int _x;
		int _y;
		irr::core::vector3df _nodePosition;
		const entity _e;
		bool _exist = true;
	private:
};

#endif /* !AENTITY_HPP_ */
