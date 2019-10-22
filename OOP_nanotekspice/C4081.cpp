/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4081 4 AND class
*/

#include "C4081.hpp"

// === INIT ===
C4081::C4081() : 
	AGate(14)
{
}

C4081::~C4081()
{
}

// === COMPUTE ===
nts::Tristate C4081::compute(std::size_t pin) {
	if (pin == 3) {
		_pins[1] = _links[1].first->compute(_links[1].second);
		_pins[2] = _links[2].first->compute(_links[2].second);
		_pins[pin] = door::AND(_pins[1], _pins[2]);
	}
	if (pin == 4) {
		_pins[5] = _links[5].first->compute(_links[5].second);
		_pins[6] = _links[6].first->compute(_links[6].second);
		_pins[pin] = door::AND(_pins[5], _pins[6]);
	}
	if (pin == 10) {
		_pins[8] = _links[8].first->compute(_links[8].second);
		_pins[9] = _links[9].first->compute(_links[9].second);
		_pins[pin] = door::AND(_pins[8], _pins[9]);
	}
	if (pin == 11) {
		_pins[12] = _links[12].first->compute(_links[12].second);
		_pins[13] = _links[13].first->compute(_links[13].second);
		_pins[pin] = door::AND(_pins[12], _pins[13]);
	}
	return (_pins[pin]);
}

void C4081::dump() const
{
	std::cout << _pins[3] << std::endl;
	std::cout << _pins[4] << std::endl;
	std::cout << _pins[10] << std::endl;
	std::cout << _pins[11] << std::endl;
}