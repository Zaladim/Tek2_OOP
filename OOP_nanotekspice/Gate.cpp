/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** Gates classes
*/

#include "Gate.hpp"

std::ostream &operator<<(std::ostream &stream, const nts::Tristate &state)
{
	if (state == nts::FALSE)
		stream << "false";
	if (state == nts::TRUE)
		stream << "true";
	if (state == nts::UNDEFINED)
		stream << "U";
	return stream;
}

// === AGATE ===
AGate::AGate(size_t nbPins)
{
	for (size_t i = 0; i < nbPins; i++) {
		_pins.push_back(nts::UNDEFINED);
	}
}

AGate::~AGate()
{
}

nts::Tristate AGate::getPin(std::size_t pin) const
{
	if (pin >= _pins.size())
		return nts::UNDEFINED;
	return _pins[pin];
}

void AGate::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
	if (pin >= _pins.size())
		return;
	_links.insert(std::make_pair(pin, std::make_pair(std::unique_ptr<nts::IComponent>(&other), otherPin)));
}

// === NAMESPACE::DOOR ===
nts::Tristate door::AND(nts::Tristate in1, nts::Tristate in2) 
{
	if (in1 == nts::FALSE || in2 == nts::FALSE)
		return nts::FALSE;
	if (in1 == nts::TRUE && in2 == nts::TRUE)
		return nts::TRUE;
	return nts::UNDEFINED;
}

nts::Tristate door::NAND(nts::Tristate in1, nts::Tristate in2) 
{
	if (in1 == nts::FALSE || in2 == nts::FALSE)
		return nts::TRUE;
	if (in1 == nts::TRUE && in2 == nts::TRUE)
		return nts::FALSE;
	return nts::UNDEFINED;
}

nts::Tristate door::OR(nts::Tristate in1, nts::Tristate in2) 
{
	if (in1 == nts::FALSE && in2 == nts::FALSE)
		return nts::FALSE;
	if (in1 == nts::TRUE || in2 == nts::TRUE)
		return nts::TRUE;
	return nts::UNDEFINED;
}

nts::Tristate door::NOR(nts::Tristate in1, nts::Tristate in2) 
{
	if (in1 == nts::FALSE && in2 == nts::FALSE)
		return nts::TRUE;
	if (in1 == nts::TRUE || in2 == nts::TRUE)
		return nts::FALSE;
	return nts::UNDEFINED;
}

nts::Tristate door::XOR(nts::Tristate in1, nts::Tristate in2) 
{
	if (in1 == nts::FALSE && in2 == nts::FALSE)
		return nts::FALSE;
	if (in1 == nts::TRUE && in2 == nts::TRUE)
		return nts::FALSE;
	if (in1 == nts::UNDEFINED || in2 == nts::UNDEFINED)
		return nts::UNDEFINED;
	if (in1 == nts::FALSE || in2 == nts::FALSE)
		return nts::TRUE;
	return nts::UNDEFINED;
}

nts::Tristate door::INVERTER(nts::Tristate in) 
{
	if (in == nts::TRUE)
		return nts::FALSE;
	if (in == nts::FALSE)
		return nts::TRUE;
	return nts::UNDEFINED;
}

std::pair<nts::Tristate, nts::Tristate> door::ADD(nts::Tristate in1, nts::Tristate in2, nts::Tristate cin)
{
	nts::Tristate sout;
	nts::Tristate cout;
	nts::Tristate tmp;

	tmp = XOR(in1, in2);
	sout = XOR(tmp, cin);

	tmp = AND(tmp, cin);
	cout = AND(in1, in2);
	cout = OR(tmp, cout);

	return std::make_pair(sout, cout);
}

std::pair<nts::Tristate, nts::Tristate> door::FLIP_FLOP(nts::Tristate clk, nts::Tristate res, nts::Tristate d, nts::Tristate set, nts::Tristate q, nts::Tristate q_)
{
	if (set == nts::TRUE && res == nts::FALSE)
		return (std::make_pair(nts::TRUE, nts::FALSE));
	if (set == nts::TRUE && res == nts::TRUE)
		return (std::make_pair(nts::TRUE, nts::TRUE));
	if (set == nts::FALSE && res == nts::TRUE)
		return (std::make_pair(nts::FALSE, nts::TRUE));
	if (clk == nts::FALSE)
		return (std::make_pair(q, q_));
	if (d == nts::TRUE)
		return (std::make_pair(nts::TRUE, nts::FALSE));
	if (d == nts::FALSE)
		return (std::make_pair(nts::FALSE, nts::TRUE));
	return (std::make_pair(q, q_));
}
