/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** IComponent interface
*/

#ifndef _ICOMPONENT_HPP_
#define _ICOMPONENT_HPP_

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iterator>

class Pin;

namespace nts
{
	enum Tristate {
		UNDEFINED = (-true),
		TRUE = true,
		FALSE = false
	};

	class IComponent {
		public:
			// === INIT ===
			virtual ~IComponent () = default;

			// === SETTER ===
			virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;

			// === COMPUTE ===
			virtual nts::Tristate compute(std::size_t pin = 1) = 0;
			virtual void dump() const = 0;
	};

}

std::iostream &operator<<(std::iostream &stream, const nts::Tristate &state);

#endif /*_ICOMPONENT_HPP_*/