/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** CookManager
*/

#include "CookManager.hpp"

CookManager::CookManager() : 
	_working(false),
	_stop(false),
	_cooking(0)
{
}

CookManager::~CookManager()
{
}

void CookManager::push(std::string &cmd)
{
	std::unique_lock<std::mutex> lock(_m);
	_waiting.push(cmd);
	_cond.notify_one();
}

int CookManager::cook(float multiplier)
{
	int time;
	std::string cmd;

	while (true) {
		std::unique_lock<std::mutex> lock(_m);
		while (_waiting.empty()) {
			_cond.wait(lock);
			if (_stop) {
				return -1;
			}	
		}
		// std::cout << "Found Cook" << std::endl;
		_working = true;
		cmd = _waiting.front();
		_waiting.pop();
		_cooking++;
		lock.unlock();
		std::stringstream parse_cmd(cmd);
		if (!_stop) {
			std::cout << "Starting :";
			display_cmd(cmd);
		}
		handlePizza(cmd, multiplier);
		if (!_stop) {
			std::cout << "Finished :";
			display_cmd(cmd);
		}
		_working = false;
		_cooking--;
	}
	return -1;
}

void CookManager::handlePizza(std::string &cmd, float mult)
{
	Pizza pizza(cmd, mult);

	while(!pizza.ready() && !_stop) {
		for (auto &ingr : pizza.getRecipe()) {
			if (ingr.second > 0) {
				std::unique_lock<std::mutex> lock(_m);
				while (_ingredients[ingr.first] <= 0 && !_stop) {
					_stock_cond.wait(lock);
				}
				if (_stop)
					break;
				_ingredients[ingr.first] --;
				pizza.addIngredient(ingr.first);
			}
		}
	}
	
	std::this_thread::sleep_for(std::chrono::milliseconds(int(pizza.getPizzaTime() * 1000)));
}

void CookManager::refill(int stock) {
	std::unique_lock<std::mutex> lock(_m);
	for (auto &ingr : _ingredients) {
		ingr.second += stock;
	}
	_stock_cond.notify_all();
}

void CookManager::stop() 
{
	_stop = true;
	_cond.notify_all();
	_stock_cond.notify_all();
}

int CookManager::getSize()
{
	return _waiting.size() + _cooking;
}

bool CookManager::getWorking()
{
	return _working;
}

int CookManager::getWaiting()
{
	return _waiting.size();
}

int CookManager::getCooking()
{
	return _cooking;
}

std::unordered_map<Ingredients, int> CookManager::getIngredients()
{
	return _ingredients;
}

void CookManager::display_cmd(std::string cmd)
{
	std::stringstream parse_cmd(cmd);
	std::string str;

	std::getline(parse_cmd, str, ' ');
	for (auto &elem : PizzaName)
		if (elem.second == atoi(str.c_str()))
			std::cout << " " << elem.first;
	std::getline(parse_cmd, str, ' ');
	for (auto &elem : SizeMap)
		if (elem.second == atoi(str.c_str()))
			std::cout << " " << elem.first;
	std::cout << std::endl;
}