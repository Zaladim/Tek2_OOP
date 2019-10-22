#include "dyn2.hpp"
#include <iostream>


extern "C" Dyn2* entryPoint()
{
	return new Dyn2;
}

Dyn2::Dyn2() : 
	name("Kiwi")
{
	std::cout << "Kiwi" << std::endl;
}

Dyn2::~Dyn2()
{
	std::cout << "Karibou" << std::endl;
}

void Dyn2::init()
{

	std::cout << "Init Dyn2" << std::endl;
}

void Dyn2::stop()
{
	std::cout << "Stop Dyn2" << std::endl;
}

const std::string &Dyn2::getName() const
{
	return name;
}