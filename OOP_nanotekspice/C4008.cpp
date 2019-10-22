/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** C4008 8 bit adder
*/

#include "C4008.hpp"

C4008::C4008() :
	AGate(16)
{
	
}

C4008::~C4008()
{
}

nts::Tristate C4008::compute(std::size_t pin)
{
	std::pair<nts::Tristate, nts::Tristate> out;

	if (pin == 10) {
		_pins[6] = _links[6].first->compute(_links[6].second);
		_pins[7] = _links[7].first->compute(_links[7].second);
		_pins[9] = _links[9].first->compute(_links[9].second);
		out = door::ADD(_pins[6], _pins[7], _pins[9]);
		_pins[10] = out.first;
	}
	if (pin == 11) {
		_pins[4] = _links[4].first->compute(_links[4].second);
		_pins[5] = _links[5].first->compute(_links[5].second);
		compute(10);
		out = door::ADD(_pins[4], _pins[5], _pins[14]);
		_pins[11] = out.first;
	}
	if (pin == 12) {
		_pins[2] = _links[2].first->compute(_links[2].second);
		_pins[3] = _links[3].first->compute(_links[3].second);
		compute(11);
		out = door::ADD(_pins[2], _pins[3], _pins[14]);
		_pins[12] = out.first;
	}
	if (pin == 13) {
		_pins[15] = _links[15].first->compute(_links[15].second);
		_pins[1] = _links[1].first->compute(_links[1].second);
		compute(12);
		out = door::ADD(_pins[15], _pins[1], _pins[14]);
		_pins[13] = out.first;
	}
	if (pin == 14) {
		std::size_t to_compute = 0;
		if (_pins[6] != nts::UNDEFINED && _pins[7] != nts::UNDEFINED) {
			to_compute = 10;
			if (_pins[4] != nts::UNDEFINED && _pins[5] != nts::UNDEFINED) {
				to_compute++;
				if (_pins[2] != nts::UNDEFINED && _pins[3] != nts::UNDEFINED) {
					to_compute++;
					if (_pins[1] != nts::UNDEFINED && _pins[15] != nts::UNDEFINED)
						to_compute++;
				}
			}
		}
		if (to_compute)
			compute(to_compute);
		else
			_pins[14] = nts::UNDEFINED;
		return (_pins[14]);
	}
	_pins[14] = out.second;
	return (_pins[pin]);
}

void C4008::dump() const
{
	std::cout << _pins[13] << std::endl;
	std::cout << _pins[12] << std::endl;
	std::cout << _pins[11] << std::endl;
	std::cout << _pins[10] << std::endl;
	std::cout << _pins[14] << std::endl;
}