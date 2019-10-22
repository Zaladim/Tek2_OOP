/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4011 Four Nand
*/

#ifndef C4011_HPP_
#define C4011_HPP_

#include "Gate.hpp"

class C4011 : public AGate {
	public:
		C4011();
		~C4011();

	// === COMPUTE ===
		virtual nts::Tristate compute(std::size_t pin = 1) override;
		virtual void dump() const override;

	protected:
	private:
		std::vector<IComponent *> _comps;
};

#endif /* !C4011_HPP_ */
