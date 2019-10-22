/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** gates classes
*/

#ifndef GATE_HPP_
#define GATE_HPP_

#include "IComponent.hpp"

class AGate : public nts::IComponent {
	public:
		// === INIT ===
		AGate(std::size_t nbPins);
		~AGate();

		// === GETTER ===
		nts::Tristate getPin(std::size_t pin) const;

		// === SETTER ===
		void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

		// === COMPUTE ===
		virtual nts::Tristate compute(std::size_t pin = 1) = 0;
		virtual void dump() const = 0;
	protected:
		std::vector<nts::Tristate> _pins;
		std::unordered_map<std::size_t, std::pair<std::unique_ptr<nts::IComponent>, std::size_t> > _links;
		std::vector<std::size_t> _outputs;
};

namespace door
{
	nts::Tristate AND(nts::Tristate in1, nts::Tristate in2);
	nts::Tristate NAND(nts::Tristate in1, nts::Tristate in2);
	nts::Tristate OR(nts::Tristate in1, nts::Tristate in2);
	nts::Tristate XOR(nts::Tristate in1, nts::Tristate in2);
	nts::Tristate NOR(nts::Tristate in1, nts::Tristate in2);
	nts::Tristate INVERTER(nts::Tristate in);
	std::pair<nts::Tristate, nts::Tristate> ADD(nts::Tristate in1, nts::Tristate in2, nts::Tristate cin);
	std::pair<nts::Tristate, nts::Tristate> FLIP_FLOP(nts::Tristate clk, nts::Tristate res, nts::Tristate d, nts::Tristate set, nts::Tristate q, nts::Tristate q_);
}

#endif /* !GATE_HPP_ */
