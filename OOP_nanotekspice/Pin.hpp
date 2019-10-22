/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** Input and outputs class
*/

#ifndef PIN_HPP_
#define PIN_HPP_

#include "IComponent.hpp"

class Input : public nts::IComponent {
	public:
		// === INIT ===
		Input(nts::Tristate state = nts::UNDEFINED, bool stuck = false);
		~Input();

		// === SETTER ===
		void setLink(std::size_t APin, nts::IComponent &other, std::size_t otherAPin);
		void setState(nts::Tristate state);

		// === COMPUTE ===
		nts::Tristate compute(std::size_t pin = 1);
		void dump() const;

	protected:
		nts::Tristate _state;
		bool _stuck;
};

class Output : public nts::IComponent {
	public:
		// === INIT ===
		Output(nts::Tristate state = nts::UNDEFINED);
		~Output();

		// === SETTER ===
		void setLink(std::size_t APin, nts::IComponent &other, std::size_t otherAPin);
		void setState(nts::Tristate state);

		// === COMPUTE ===
		nts::Tristate compute(std::size_t pin = 1);
		void dump() const;

	private:
		nts::Tristate _state;
		std::unordered_map<std::size_t, std::pair<std::unique_ptr<nts::IComponent>, std::size_t> > _links;
};

#endif /* !PIN_HPP_ */