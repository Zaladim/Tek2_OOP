/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4030 4 XOR class
*/

#ifndef C4030_HPP_
#define C4030_HPP_

#include "Gate.hpp"

class C4030 : public AGate {
	public:
		// === INIT ===
		C4030();
		~C4030();

		// === COMPUTE ===
		virtual nts::Tristate compute(std::size_t pin = 1) override;
		virtual void dump() const override;

	protected:
	private:
};

#endif /* !C4030_HPP_ */