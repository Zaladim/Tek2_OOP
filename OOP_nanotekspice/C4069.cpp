/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** C4069 6 inverter class
*/

#include "C4069.hpp"

C4069::C4069() :
	AGate(14)
{
}

C4069::~C4069()
{
}

nts::Tristate C4069::compute(std::size_t pin)
{
	if (pin <= 6) {
		_pins[pin - 1] = _links[pin - 1].first->compute(_links[pin - 1].second);
		_pins[pin] = door::INVERTER(_pins[pin - 1]);
	}
	if (pin >= 8) {
		_pins[pin + 1] = _links[pin + 1].first->compute(_links[pin + 1].second);
		_pins[pin] = door::INVERTER(_pins[pin + 1]);
	}
	return (_pins[pin]);
}

void C4069::dump() const
{
	for (int i = 2; i < 14; i += 2)
		std::cout << _pins[i] << std::endl;
}