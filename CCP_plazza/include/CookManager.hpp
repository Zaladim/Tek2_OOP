/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** CookManager
*/

#ifndef CookManager_HPP_
#define CookManager_HPP_

#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <sstream>
#include "Pizza.hpp"

class CookManager {
	public:
		CookManager();
		~CookManager();

		void push(std::string &cmd);
		int cook(float multiplier);
		void handlePizza(std::string &cmd, float mult);

		void stop();

		int getSize();
		bool getWorking();
		int getCooking();
		int getWaiting();
		std::unordered_map<Ingredients, int> getIngredients();

		void refill(int stock);

	protected:
	private:
		void display_cmd(std::string cmd);

		std::queue<std::string> _waiting;
		int _cooking;
		std::mutex _m;
		std::condition_variable _cond;
		std::condition_variable _stock_cond;
		bool _working;
		bool _stop;

		std::unordered_map<Ingredients, int> _ingredients = {
			{DOE, 5},
			{TOMATO, 5},
			{GRUYERE, 5},
			{HAM, 5},
			{MUSHROOM, 5},
			{STEAK, 5},
			{EGGPLANT, 5},
			{GOAT, 5},
			{LOVE, 5},
			{FRY, 5},
			{BEER, 5}
		};
};

#endif /* !CookManager_HPP_ */
