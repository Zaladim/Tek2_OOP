/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** Pizza
*/

#include "Pizza.hpp"

Pizza::Pizza(std::string &cmd, float mult)
{
	unpack(cmd, mult);
}

Pizza::~Pizza()
{
}

void Pizza::unpack(std::string &cmd, float mult)
{
    std::vector<std::string> parameters = parser(cmd, ' ');

	_type = PizzaType(atoi(parameters[0].c_str()));
	_size = PizzaSize(atoi(parameters[1].c_str()));
    _pizza_time = CookTime[_type] * mult;
	for (Ingredients &ingr : PizzaRecipe[_type]) {
        _recipe[ingr] += _size;
    }
}

std::string Pizza::pack(void)
{
    std::string cmd = "c: " + std::to_string(_type) + " " + std::to_string(_size);
    return (cmd);
}

PizzaType Pizza::getPizzaType(void) const
{
    return (_type);
}

PizzaSize Pizza::getPizzaSize(void) const
{
    return (_size);
}

float Pizza::getPizzaTime(void) const
{
    return (_pizza_time);
}

std::unordered_map<Ingredients, int> Pizza::getRecipe(void) const
{
	return (_recipe);
}

void Pizza::setPizzaType(PizzaType type)
{
    _type = type;
}

void Pizza::setPizzaSize(PizzaSize size)
{
    _size = size;
}

// void Pizza::setPizzaTime(unsigned int pizza_time)
// {
// 	switch(_type) {
// 		case (Regina):
// 			break;
// 		case (Margarita):
// 			break;
// 		case (Americana):
// 			break;
// 		case (Fantasia):
// 			break;
// 	}
// }

void Pizza::addIngredient(Ingredients ingr)
{
	_recipe[ingr]--;
}

bool Pizza::ready()
{
	for (auto &ingr : _recipe) {
		if (ingr.second > 0) {
			return false;
		}
	}
	return true;
}