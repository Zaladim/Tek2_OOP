/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4071 Four NOR 
*/

#ifndef C4071_HPP_
#define C4071_HPP_

#include "Gate.hpp"

class C4071 : public AGate {
	public:
		// === INIT ===
		C4071();
		~C4071();

		// === COMPUTE ===
		nts::Tristate compute(std::size_t pin = 1) override;
		void dump() const override;

	protected:
	private:
};

#endif /* !C4071_HPP_ */
