/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** Clock class
*/

#include "Clock.hpp"

Clock::Clock(nts::Tristate state) : 
	Input(state)
{
}

Clock::~Clock()
{
}

nts::Tristate Clock::compute(std::size_t pin)
{
	nts::Tristate last = _state;
	if (pin == 0 || pin == 1){
		_state = door::INVERTER(_state);
	}
	return last;
}