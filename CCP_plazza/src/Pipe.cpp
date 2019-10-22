/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** Pipe IPC
*/

#include "Pipe.hpp"

Pipe::Pipe(const std::string name) : 
	_name(name),
	_file("./tmp/" + name)
{
	mkfifo(_file.c_str(), 0666);
}

Pipe::~Pipe()
{
	destroy();
}

std::string Pipe::getName() const
{
	return _name;
}

bool Pipe::read(std::string &msg) const
{
	std::ifstream file(_file.data(), std::ios::in);

	getline(file, msg);
	file.close();
	return true;
}

bool Pipe::write(const std::string &msg) const
{
	std::ofstream file;

	file.open(_file.data());
	file << msg;
	file << "\n";
	file.close();
	return true;
}

void Pipe::destroy()
{
	unlink(this->_file.c_str());
}