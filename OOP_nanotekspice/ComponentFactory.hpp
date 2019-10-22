/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** ComponentFactory factory class
*/

#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_

#include <memory>
#include <functional>
#include <string>
#include "C4001.hpp"
#include "C4008.hpp"
#include "C4011.hpp"
#include "C4013.hpp"
#include "C4030.hpp"
#include "C4069.hpp"
#include "C4071.hpp"
#include "C4081.hpp"
#include "IComponent.hpp"

class ComponentFactory {
	public:
		// === INIT ===
		ComponentFactory();
		~ComponentFactory();

		// === FACTORY START ===
		std::unique_ptr<nts::IComponent> createComponent(const std::string &type, const std::string &value);

	protected:
	private:
		std::unordered_map<std::string,std::function<std::unique_ptr<nts::IComponent>(const std::string&)>> _components;

		// === FACTORY ===
		std::unique_ptr<nts::IComponent> create4001(const std::string &value) const noexcept {
			std::unique_ptr<nts::IComponent> comp(new C4001());
			return (comp);
		}
		std::unique_ptr<nts::IComponent> create4008(const std::string &value) const noexcept {
			std::unique_ptr<nts::IComponent> comp(new C4008());
			return (comp);
		}
		std::unique_ptr<nts::IComponent> create4011(const std::string &value) const noexcept {
			std::unique_ptr<nts::IComponent> comp(new C4011());
			return (comp);
		}
		std::unique_ptr<nts::IComponent> create4013(const std::string &value) const noexcept {
			std::unique_ptr<nts::IComponent> comp(new C4013());
			return (comp);
		}
		std::unique_ptr<nts::IComponent> create4017(const std::string &value) const noexcept;
		std::unique_ptr<nts::IComponent> create4030(const std::string &value) const noexcept {
			std::unique_ptr<nts::IComponent> comp(new C4030());
			return (comp);
		}
		std::unique_ptr<nts::IComponent> create4040(const std::string &value) const noexcept;
		std::unique_ptr<nts::IComponent> create4069(const std::string &value) const noexcept {
			std::unique_ptr<nts::IComponent> comp(new C4069());
			return (comp);
		}
		std::unique_ptr<nts::IComponent> create4071(const std::string &value) const noexcept {
			std::unique_ptr<nts::IComponent> comp(new C4071());
			return (comp);
		}
		std::unique_ptr<nts::IComponent> create4081(const std::string &value) const noexcept {
			std::unique_ptr<nts::IComponent> comp(new C4081());
			return (comp);
		}
		std::unique_ptr<nts::IComponent> create4094(const std::string &value) const noexcept;
		std::unique_ptr<nts::IComponent> create4514(const std::string &value) const noexcept;
		std::unique_ptr<nts::IComponent> create4801(const std::string &value) const noexcept;
		std::unique_ptr<nts::IComponent> create4716(const std::string &value) const noexcept;
};

#endif /* !COMPONENTFACTORY_HPP_ */
