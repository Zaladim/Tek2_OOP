/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>
#include "../AGame.hpp"

#include <iostream>

class Object {
	public:
		~Object();

		// === GETTER ===
		int getPosX() const;
		int getPosY() const;
		int getType() const;

		virtual int isThere(int x, int y);

        // === SETTER ===
        void setPos(int x, int y);
		void setGround(int value);

		// === ACTIONS ===
		void move(int hor, int ver);
		void unsetMap(std::vector<std::vector<int>> &board);
		void setMap(std::vector<std::vector<int>> &board);

	protected:
        int _x;
        int _y;
		int _value;
		int _ground;
		Object(int x, int y, int value);
};

#endif /* !OBJECT_HPP_ */