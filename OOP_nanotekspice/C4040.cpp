/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4040 Component
*/

#include "C4040.hpp"

C4040::C4040() :
	AGate(16)
{
}

C4040::~C4040()
{
}

nts::Tristate C4040::compute(std::size_t pin)
{
	if (pin == 9) {
		_pins[10] = _links[10].first->compute(_links[10].second);
		_pins[11] = _links[11].first->compute(_links[11].second);
		nts::Tristate tmp1 = _pins[10];
		nts::Tristate tmp2 = _pins[11];
		nts::Tristate tmp3 = door::NOR(tmp1, tmp2);

		tmp1 = door::NOR(tmp1, tmp2);
		tmp2 = door::INVERTER(tmp2);

	}
	
	return (_pins[pin]);
}

void C4040::dump() const
{
	std::cout << _pins[3] << std::endl;
	std::cout << _pins[4] << std::endl;
	std::cout << _pins[10] << std::endl;
	std::cout << _pins[11] << std::endl;
}