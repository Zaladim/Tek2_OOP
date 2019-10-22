/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** ComponentFactory class
*/

#include "ComponentFactory.hpp"

ComponentFactory::ComponentFactory()
{
	_components = {
    {"4001", [&](auto e) -> std::unique_ptr<nts::IComponent> { return(this->create4001(e)); }},
    {"4008", [&](auto e) -> std::unique_ptr<nts::IComponent> { return(this->create4008(e)); }},
    {"4011", [&](auto e) -> std::unique_ptr<nts::IComponent> { return(this->create4011(e)); }},
    {"4013", [&](auto e) -> std::unique_ptr<nts::IComponent> { return(this->create4013(e)); }},
    {"4030", [&](auto e) -> std::unique_ptr<nts::IComponent> { return(this->create4030(e)); }},
    {"4069", [&](auto e) -> std::unique_ptr<nts::IComponent> { return(this->create4069(e)); }},
    {"4071", [&](auto e) -> std::unique_ptr<nts::IComponent> { return(this->create4071(e)); }},
    {"4081", [&](auto e) -> std::unique_ptr<nts::IComponent> { return(this->create4081(e)); }},
};
}

ComponentFactory::~ComponentFactory()
{
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComponent(const std::string &type, const std::string &value)
 {
	return ((this->_components[type])(value));
}
