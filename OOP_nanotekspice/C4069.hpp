/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** C4069 6 Inverter class
*/

#ifndef C4069_HPP_
#define C4069_HPP_

#include "Gate.hpp"

class C4069 : public AGate {
	public:
		// === INIT ===
		C4069();
		~C4069();

		// === COMPUTE ===
		nts::Tristate compute(std::size_t pin = 1) override;
		void dump() const override;

	protected:
	private:
};

#endif /* !C4069_HPP_ */
