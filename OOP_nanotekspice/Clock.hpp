/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** Clock class
*/

#include "Pin.hpp"
#include "Gate.hpp"

class Clock : public Input {
	public:
		// === INIT ===
		Clock(nts::Tristate state = nts::UNDEFINED);
		~Clock();

		// === COMPUTE ===
		nts::Tristate compute(std::size_t pin = 1) override;
};