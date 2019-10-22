/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4081 4 AND class
*/

#ifndef C4081_HPP_
#define C4081_HPP_

#include "Gate.hpp"

class C4081 : public AGate {
	public:
		// === INIT ===
		C4081();
		~C4081();

		// === COMPUTE ===
		virtual nts::Tristate compute(std::size_t pin = 1) override;
		virtual void dump() const override;

	protected:
	private:
};

#endif /* !C4081_HPP_ */
