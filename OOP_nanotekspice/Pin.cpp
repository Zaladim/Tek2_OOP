/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** Pins class
*/

#include "Pin.hpp"

// === INPUT ===
Input::Input(nts::Tristate state, bool stuck) :
	_state(state),
	_stuck(stuck)
{
}

Input::~Input()
{
}

// === SETTER ===
void Input::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
	other.setLink(otherPin, *this, pin);
}

void Input::setState(nts::Tristate state)
{
	if (!_stuck)
		_state = state;
}


// === COMPUTE ===
nts::Tristate Input::compute(std::size_t pin)
{
	if (pin == 1 || pin == 0)
		return _state;
}

void Input::dump() const
{
	std::cout << _state << std::endl;
}

// === OUTPUT ===
Output::Output(nts::Tristate state) :
	_state(state)
{
}

Output::~Output()
{
}


// === SETTER ===
void Output::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
	if (_links.size() == 1) {
		std::cerr << "only one link for each output" << std::endl;
		return;
	}
	if (pin == 1 || pin == 0) {
		_links.insert(std::make_pair(0, std::make_pair(std::unique_ptr<nts::IComponent>(&other), otherPin)));
	}
}

void Output::setState(nts::Tristate state)
{
	_state = state;
}

// === COMPUTE ===
nts::Tristate Output::compute(std::size_t pin)
{
	if (pin == 1 || pin == 0)
		_state = _links[0].first->compute(_links[0].second);
	return (_state);
}

void Output::dump() const
{
	std::cout << _state << std::endl;
}