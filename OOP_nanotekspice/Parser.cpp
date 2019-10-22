/*
** EPITECH PROJECT, 2019
** NANO TEK SPICE
** File description:
** Parser class
*/

#include "Parser.hpp"

// === INIT ===
Parser::Parser(std::string &filename, int ac, char **av)
{
    std::ifstream file(filename);
    std::string line;
    std::string pin;

    while (getline(file, line)) {
        if (line.compare(".chipsets:") == 0)
            setPins(file);
    }
    for (int i = 2; i < ac; i++) {
        line = av[i];
		pin = line.substr(0, line.find("="));
		line = line.substr(line.find("=") + 1, line.length());
		if (_inputs.find(pin) != _inputs.end()) {
			static_cast<Input *>(_inputs[pin])->setState(static_cast<nts::Tristate>(std::stoi(line)));
		}
		if (_outputs.find(pin) != _outputs.end()) {
			static_cast<Output *>(_outputs[pin])->setState(static_cast<nts::Tristate>(std::stoi(line)));
		}
    }
}

Parser::~Parser()
{
}

// === SETTER ===
void Parser::setPins(std::ifstream &file) 
{
    std::string line;
    std::string word;
    while (getline(file, line)) {
        if (line.compare(".links:") == 0) {
            setLinks(file);
			break;
		}
    	std::istringstream iss(line);
        iss >> word;
        if (word.compare("input") == 0) {
            iss >> word;
            _inputs.insert(std::make_pair(word, new Input()));
        } else if (word.compare("true") == 0) {
            iss >> word;
            _inputs.insert(std::make_pair(word, new Input(nts::Tristate::TRUE, true)));
        } else if (word.compare("false") == 0) {
            iss >> word;
            _inputs.insert(std::make_pair(word, new Input(nts::Tristate::FALSE, true)));
        } else if (word.compare("clock") == 0) {
            iss >> word;
            _inputs.insert(std::make_pair(word, new Clock()));
        } else if (word.compare("output") == 0) {
            iss >> word;
            _outputs.insert(std::make_pair(word, new Output()));
			_ordered_out.push_back(word);
        } else if (!line.empty() && line[0] != '#'){
             iss >> line;
            _comp.insert(std::make_pair(line, fact.createComponent(word, line)));
        }
    }
}

void Parser::setLinks(std::ifstream &file)
{
    std::string line;
    std::string word;
	std::pair<std::string, std::string> pin;
	std::pair<std::string, std::string> comp;

    while (getline(file, line)) {
		if (!line.empty()) {
			std::istringstream iss(line);
			iss >> word;
			pin = (std::make_pair(word.substr(0, word.find(":")), word.substr(word.find(":") + 1, word.length())));
			iss >> word;
			comp = (std::make_pair(word.substr(0, word.find(":")), word.substr(word.find(":") + 1, word.length())));
			if (_comp.find(pin.first) != _comp.end()) {
				if (_comp.find(comp.first) != _comp.end()) {
					_comp[comp.first]->setLink(std::stoi(comp.second), *_comp[pin.first], std::stoi(pin.second));
				} else if (_inputs.find(comp.first) != _inputs.end()) {
					_comp[pin.first]->setLink(std::stoi(pin.second), *_inputs[comp.first], std::stoi(comp.second));
				} else if (_outputs.find(comp.first) != _outputs.end()) {
					_outputs[comp.first]->setLink(std::stoi(comp.second), *_comp[pin.first], std::stoi(pin.second));
				}
			} else if (_outputs.find(pin.first) != _outputs.end()) {
				if (_comp.find(comp.first) != _comp.end()) {
					_outputs[pin.first]->setLink(std::stoi(pin.second), *_comp[comp.first], std::stoi(comp.second));
				} else if (_inputs.find(comp.first) != _inputs.end()) {
					_outputs[pin.first]->setLink(std::stoi(pin.second), *_inputs[comp.first], std::stoi(comp.second));
				}
			} else if (_inputs.find(pin.first) != _inputs.end()) {
				if (_comp.find(comp.first) != _comp.end()) {
					_inputs[pin.first]->setLink(std::stoi(pin.second), *_comp[comp.first], std::stoi(comp.second));
				} else if (_inputs.find(comp.first) != _inputs.end()) {
					_inputs[pin.first]->setLink(std::stoi(pin.second), *_inputs[comp.first], std::stoi(comp.second));
				} else if (_outputs.find(comp.first) != _outputs.end()) {
					_outputs[comp.first]->setLink(std::stoi(comp.second), *_inputs[pin.first], std::stoi(pin.second));
				}
			}
		}
	}
}

// === COMMAND ===
void Parser::compute()
{
	for (std::string &comp : _ordered_out) {
		_outputs[comp]->compute();
	}
}

void Parser::display()
{
	for (std::string &comp : _ordered_out) {
		std::cout << comp << "=";
		_outputs[comp]->dump();
	}
}

void Parser::dump()
{
	for (auto &pair : _comp) {
		pair.second->dump();
	}
}

void Parser::change_input(std::string &line)
{
	std::regex regex("^.*=.*$");
	if (!std::regex_match(line, regex) || line.find(" ") != std::string::npos) {
		std::cerr << "Wrong input" << std::endl;
		return;
	}
	std::string pin = line.substr(0, line.find("="));
	line = line.substr(line.find("=") + 1, line.length());
	if (std::stoi(line) > 1 || std::stoi(line) < -1) {
		std::cerr << "Wrong input" << std::endl;
		return;
	}
	if (_inputs.find(pin) != _inputs.end()) {
		static_cast<Input *>(_inputs[pin])->setState(static_cast<nts::Tristate>(std::stoi(line)));
	}
}

bool cont = true;

static void sigHandler(int sig)
{
	cont = false;
}

void Parser::loop()
{
	cont = true;
	signal(SIGINT, sigHandler);
	while (cont) {
		compute();
		display();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}