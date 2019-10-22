/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4040 Counter
*/

#ifndef C4040_HPP_
#define C4040_HPP_

#include "Gate.hpp"

class C4040 : public AGate {
	public:
		// === INIT ===
		C4040();
		~C4040();

		// === COMPUTE ===
		nts::Tristate compute(std::size_t pin = 1) override;
		void dump() const override;

	protected:
	private:
};

#endif /* !C4040_HPP_ */
