/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4008 8 bit adder
*/

#ifndef C4008_HPP_
#define C4008_HPP_

#include "Gate.hpp"

class C4008 : public AGate {
	public:
		// === INIT ===
		C4008();
		~C4008();

		// === COMPUTE ===
		virtual nts::Tristate compute(std::size_t pin = 1) override;
		virtual void dump() const override;

	protected:
	private:
};

#endif /* !C4008_HPP_ */
