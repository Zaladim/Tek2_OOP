#include "Parser.hpp"

int main(int ac, char **av)
{
	try {
		Parser parser(*new std::string(av[1]), ac, av);
		parser.compute();
		parser.display();
		std::cout << "> ";
		for (std::string line; std::getline(std::cin, line);) {
			if (!line.compare("exit")) {
				return (0);
			}
			else if (!line.compare("display"))
				parser.display();
			else if (!line.compare("simulate"))
				parser.compute();
			else if (!line.compare("dump"))
				parser.dump();
			else if (!line.compare("loop"))
				parser.loop();
			else
				parser.change_input(line);
			std::cout << "> ";
		}
	} catch (const std::exception &e) {
		return (84);
	};
	return (0);
}