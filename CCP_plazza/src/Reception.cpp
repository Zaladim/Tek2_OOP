/*
** EPITECH PROJECT, 2019
**
** File description:
**
*/

//buy USDT_ETH 1

#include "Reception.hpp"

Reception::Reception(float multiplier_cooking_time, int cooks_per_kitchen, int time):
	_multiplier_cooking_time(multiplier_cooking_time),
	_cooks_per_kitchen(cooks_per_kitchen),
	_time(time)
{
}

Reception::~Reception()
{
	for (Pipe *elem : _kitchens) {
		elem->write("r: quit");
	}
}

void Reception::welcome()
{
	std::cout << "Welcome to the Plazza!" << std::endl;
	menu();
}

void Reception::menu()
{
	int len = PizzaName.size();

	std::cout << "Available Pizzas :" << std::endl;
	for (int i = 0; i < len; i++)
		for (auto &pizza : PizzaName)
			if (pizza.second == pow(2, i)){
				std::cout << "\t - " << pizza.first << std::endl;
				break;
			}

	std::cout << "Available Size :" << std::endl;
	len = SizeMap.size();
	for (int i = 0; i < len; i++)
		for (auto &size : SizeMap)
			if(size.second == pow(2, i)) {
				std::cout << "\t - " << size.first << std::endl; 
				break;
			}
}

void Reception::help()
{
	std::cout << " - status : Display kitchens" << std::endl;
	std::cout << " - menu : Display menu" << std::endl;
	std::cout << " - help : Display this message" << std::endl;
	std::cout << " - quit : Leave the Plazza" << std::endl;
}

int is_a_pizza(std::string name)
{
	for (auto &pizza : PizzaName) {
		if (name == pizza.first)
			return pizza.second;
	}
	return -1;
}

int is_a_size(std::string size)
{
	for (auto &pizza : SizeMap) {
		if (size == pizza.first)
			return pizza.second;
	}
	return -1;
}

int is_a_number(std::string str_numb)
{
	int numb;

	if (str_numb[0] == 'x') {
			numb = atoi(str_numb.c_str() + 1);
			return (numb);
	}
	return -1;
}

void Reception::run()
{
	std::string command;
	std::vector<std::string> parameters;
	std::vector<std::string> commands;
	bool run = true;

	welcome();

	while (run) {
		std::cout << ">";
		getline(std::cin, command);
		cleanKitchen();
		commands = parser(command, ';');
		for (auto &cmd : commands) {
			while (cmd[0] == ' ') {
				cmd.erase(0, 1);
			}
			if (cmd == "quit") {
				run = false;
				break;
			}
			if (cmd == "status") {
				status();
				continue;
			}
			if (cmd == "menu") {
				menu();
				continue;
			}
			if (cmd == "help") {
				help();
				continue;
			}
			parameters = parser(cmd, ' ');
			do_command(parameters);
		}
	}
	for (auto &pipe : _kitchens) {
		pipe->write("r: quit");
	}
}

int Reception::do_command(std::vector<std::string> parameters)
{
	unsigned int pizza, size, number;

	if (parameters.size() == 3) {
		pizza = is_a_pizza(parameters[0]);
		size = is_a_size(parameters[1]);
		number = is_a_number(parameters[2]);
		if (pizza == -1) {
				std::cerr<<"wrong pizza name."<<std::endl;
				return (1);
		}
		if (size == -1) {
				std::cerr<<"wrong pizza size."<<std::endl;
				return (1);
		}
		if (number == -1) {
				std::cerr<<"wrong pizza number."<<std::endl;
				return (1);
		}
		std::cout<<"you commanded "<< number <<" "<<size<<" "<<pizza<<"."<<std::endl;
		std::string tmp = "c: " + std::to_string(pizza) + " " + std::to_string(size);
		for (int i = 0; i < number; i++) {
			std::cout << "Pizza n° " << i << std::endl;
			commandHandler(tmp);
			std::cout << "pizza n° " << i << " send" << std::endl;
		}
		return (EXIT_SUCCESS);
	} else {
		if (parameters.size() != 0)
			std::cerr<<"unknown command."<<std::endl;
		return (1);
	}
}

void Reception::status()
{
	std::string tmp;

	if (_kitchens.size() == 0)
		std::cout << "No Kitchens" << std::endl;
	for (auto &pipe : _kitchens) {
		std::cout << "Asking " << pipe->getName() << " status :" << std::endl;
		pipe->write("r: status");
		pipe->read(tmp);
		while (tmp.substr(0, 2) == "c:" || tmp.substr(0, 2) == "r:") {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			pipe->read(tmp);
		}
	}
}

void Reception::commandHandler(std::string &cmd)
{
	std::string tmp;
	_currentKitchen = NULL;
	selectKitchen();
	if (!_currentKitchen) {
		std::cout << "No kitchen available, creating new kitchen" << std::endl;
		createKitchen();
		selectKitchen();
	}
	_currentKitchen->write(cmd);
	_currentKitchen->read(tmp);
	while(tmp != "OK") {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		_currentKitchen->read(tmp);
	}
}

void Reception::createKitchen()
{
	pid_t pid;
	std::string name = "kitchen_" + std::to_string(_kitchens.size());

	pid = fork();
	if (pid < 0) {
		throw std::exception();
	}
	if (pid == 0) {
		Kitchen *kitchen = new Kitchen(name, _cooks_per_kitchen, _multiplier_cooking_time, _time);
		kitchen->run();
		delete(kitchen);
		exit(EXIT_SUCCESS);
	} else {
		_kitchens.push_back(new Pipe(name));
	}
}

void Reception::selectKitchen()
{
	std::string tmp;
	int current = (_cooks_per_kitchen * 2);

	for (auto &pipe : _kitchens) {
		std::cout << "Asking " << pipe->getName() << " if available" << std::endl;
		pipe->write("r: nbAwaiting");
		if (pipe->read(tmp)) {
			while (tmp.substr(0, 2) == "c:" || tmp.substr(0, 2) == "r:") {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				pipe->read(tmp);
			}
			if (atoi(tmp.c_str()) < current) {
				std::cout << "Found Kitchen " << pipe->getName() << std::endl; 
				current = atoi(tmp.c_str());
				_currentKitchen = pipe;
			}
		}
	}
}

void Reception::cleanKitchen()
{
	std::vector<Pipe *>::iterator it = _kitchens.begin();
	while (it != _kitchens.end()) {
		fs::path path("./tmp/" + (*it)->getName());
		if ((access(path.c_str(), F_OK)) == -1) {
			_kitchens.erase(it);
		} else {
			it++;
		}
	}
}


