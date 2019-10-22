/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4001 Four NOR 
*/

#ifndef C4001_HPP_
#define C4001_HPP_

#include "Gate.hpp"

class C4001 : public AGate {
	public:
		// === INIT ===
		C4001();
		~C4001();

		// === COMPUTE ===
		nts::Tristate compute(std::size_t pin = 1) override;
		void dump() const override;

	protected:
	private:
};

#endif /* !C4001_HPP_ */
