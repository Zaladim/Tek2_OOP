/*
** EPITECH PROJECT, 2019
** PLAZZA 
** File description:
** Pizza abtract class
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <unordered_map>
#include <string>
#include <sstream>
#include "Plazza.hpp"

enum PizzaType
{
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8,
        Belgian = 16
};
                
enum PizzaSize 
{
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16,
        G = 32
};

enum Ingredients
{
    DOE = 0,
    TOMATO = 1,
    GRUYERE = 2,
    HAM = 3,
    MUSHROOM = 4,
    STEAK = 5,
    EGGPLANT = 6,
    GOAT = 7,
    LOVE = 8,
    FRY = 9,
    BEER = 10
};

static std::unordered_map<std::string, PizzaSize> SizeMap = {
    {"S", S},
    {"M", M},
    {"L", L},
    {"XL", XL},
    {"XXL", XXL},
    {"G", G}
};

static std::unordered_map<PizzaType, int> CookTime = {
	{Margarita, 1},
	{Regina, 2},
	{Americana, 2},
	{Fantasia, 4},
	{Belgian, 5}
};

static std::unordered_map<std::string, PizzaType> PizzaName = {
	{"Margarita", Margarita},
	{"Regina", Regina},
	{"Americana", Americana},
	{"Fantasia", Fantasia},
	{"Belgian", Belgian}
};

static std::unordered_map<PizzaType, std::vector<Ingredients>> PizzaRecipe = {
	{Margarita, {DOE, TOMATO, GRUYERE}},
	{Regina, {DOE, TOMATO, GRUYERE, HAM, MUSHROOM}},
    {Americana, {DOE, TOMATO, GRUYERE, HAM, MUSHROOM}},
    {Fantasia, {DOE, TOMATO, EGGPLANT, GOAT, LOVE}},
	{Belgian, {DOE, TOMATO, FRY, BEER}}
};

static std::unordered_map<Ingredients, std::string> ingrName = {
    {DOE, "Doe"},
    {TOMATO, "Tomato"},
    {GRUYERE, "Gruyere"},
    {HAM, "Ham"},
    {MUSHROOM, "Mushroom"},
    {STEAK, "Steak"},
    {EGGPLANT, "Eggplant"},
    {GOAT, "Goat cheese"},
    {LOVE, "Chief love"},
	{FRY, "Fry"},
	{BEER, "Beer"}
};

class Pizza {
	public:
		Pizza(std::string &cmd, float mult);
		~Pizza();
 
        std::string pack(void);
        void unpack(std::string &cmd, float mult);

        PizzaType getPizzaType(void) const;
		PizzaSize getPizzaSize(void) const;
        float getPizzaTime(void) const;
		std::unordered_map<Ingredients, int> getRecipe(void) const;
        void setPizzaType(PizzaType type);
        void setPizzaSize(PizzaSize size);
        // void setPizzaTime(unsigned int pizza_time);

		void addIngredient(Ingredients ingr);
		bool ready();
	protected:
	private:
        PizzaType _type;
		PizzaSize _size;
        float _pizza_time;
		std::unordered_map<Ingredients, int> _recipe = {
			{DOE, 0},
			{TOMATO, 0},
			{GRUYERE, 0},
			{HAM, 0},
			{MUSHROOM, 0},
			{STEAK, 0},
			{EGGPLANT, 0},
			{GOAT, 0},
			{LOVE, 0}
		};
};

#endif /* !Pizza_HPP_ */
