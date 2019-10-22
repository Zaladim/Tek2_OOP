/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4013 Component
*/

#include "C4013.hpp"

C4013::C4013() :
	AGate(14)
{
}

C4013::~C4013()
{
}

nts::Tristate C4013::compute(std::size_t pin)
{
	std::pair<nts::Tristate, nts::Tristate> out;

	if (pin == 1 || pin == 2) {
		_pins[3] = _links[3].first->compute(_links[3].second);
		_pins[4] = _links[4].first->compute(_links[4].second);
		_pins[5] = _links[5].first->compute(_links[5].second);
		_pins[6] = _links[6].first->compute(_links[6].second);
		out = door::FLIP_FLOP(_pins[3], _pins[4], _pins[5], _pins[6], _pins[1], _pins[2]);
		_pins[1] = out.first;
		_pins[2] = out.second;
	}
	if (pin == 13 || pin == 12) {
		_pins[11] = _links[11].first->compute(_links[11].second);
		_pins[10] = _links[10].first->compute(_links[10].second);
		_pins[9] = _links[9].first->compute(_links[9].second);
		_pins[8] = _links[8].first->compute(_links[8].second);
		out = door::FLIP_FLOP(_pins[11], _pins[10], _pins[9], _pins[8], _pins[13], _pins[12]);
		_pins[13] = out.first;
		_pins[12] = out.second;
	}
	return (_pins[pin]);
}

void C4013::dump() const
{
	std::cout << _pins[1] << std::endl;
	std::cout << _pins[2] << std::endl;
	std::cout << _pins[13] << std::endl;
	std::cout << _pins[12] << std::endl;
}