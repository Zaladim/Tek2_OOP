/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** 4013 class
*/

#ifndef C4013_HPP_
#define C4013_HPP_

#include "Gate.hpp"

class C4013 : public AGate {
	public:
		// === INIT ===
		C4013();
		~C4013();

		// === COMPUTE ===
		nts::Tristate compute(std::size_t pin = 1) override;
		void dump() const override;

	protected:
	private:
};

#endif /* !C4013_HPP_ */
