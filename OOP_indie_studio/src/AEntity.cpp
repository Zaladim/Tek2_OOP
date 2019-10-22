/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Entity abstract
*/

#include "AEntity.hpp"

AEntity::AEntity(int x, int y, entity e, irr::core::vector3df position) : 
_x(x),
_y(y),
_e(e),
_nodePosition(position)
{
}

AEntity::AEntity(int x, int y, entity e) : 
_x(x),
_y(y),
_e(e),
_nodePosition(irr::core::vector3df((irr::f32)x, (irr::f32)y, 20.0f))
{
}

AEntity::~AEntity()
{
	_exist = false;
}

int AEntity::getX() const
{
	return _x;
}

int AEntity::getY() const
{
	return _y;
}

irr::core::vector3df AEntity::getNode() const
{
	return _nodePosition;
}

void AEntity::setX(int x)
{
	_x = x;
}

void AEntity::setY(int y)
{
	_y = y;
}

void AEntity::setNode(float x, float y, std::vector<std::unique_ptr<AEntity>> &bombs)
{
	_nodePosition.X += x;
	_nodePosition.Y += y;

	_x = (_nodePosition.X + 5) / 10;
	_y = (_nodePosition.Y + 5) / 10;
}

entity AEntity::getEntity() const
{
	return _e;
}

std::string AEntity::getTexture(const char *textureName) {
	boost::filesystem::path p("assets");

	if (boost::filesystem::exists(p)) {
		for (auto& x : boost::filesystem::directory_iterator(p)) {
			if (x.path().filename() == textureName) {
				return x.path().string();
			}
		}
	}
	return ("");
}

AEntity *AEntity::update()
{
	if (_exist)
		return this;
	return nullptr;
}

AEntity *AEntity::destroy()
{
	_exist = false;
	return nullptr;
}

bool AEntity::operator==(const AEntity *other)
{
	if (other == nullptr)
		return false;
	if (_e == other->getEntity() && _x == other->getX() && _y == other->getY())
		return true;
	return false;
}

bool AEntity::operator!=(const AEntity *other)
{
	if (other == nullptr)
		return true;
	if (_e != other->getEntity() || _x != other->getX() || _y != other->getY())
		return true;
	return false;
}

bool AEntity::operator==(const entity e)
{
	if (_e == e)
		return true;
	return false;
}

bool AEntity::operator!=(const entity e)
{
	if (_e != e)
		return true;
	return false;
}