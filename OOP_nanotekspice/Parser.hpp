/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <chrono>
#include <thread>
#include <csignal>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include "Gate.hpp"
#include "ComponentFactory.hpp"
#include "Pin.hpp"
#include "Clock.hpp"

class Parser {
    public:
        // === INIT ===
        Parser(std::string &filename, int ac, char **av);
        ~Parser();

        // === SETTER ===
        void setPins(std::ifstream &file);
        void setLinks(std::ifstream &file);

        // === COMMAND ===
        void compute();
        void display();
        void dump();
        void loop();
        void change_input(std::string &line);

    private:
        ComponentFactory fact;
        std::unordered_map<std::string, nts::IComponent *> _inputs;
        std::unordered_map<std::string, nts::IComponent *> _outputs;
        std::unordered_map<std::string, std::unique_ptr<nts::IComponent>> _comp;
        std::vector<std::string> _ordered_out;
};


#endif /* !PARSER_HPP_ */
