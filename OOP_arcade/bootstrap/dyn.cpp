#include "dyn.hpp"
#include <iostream>


extern "C" Dyn* entryPoint()
{
	return new Dyn;
}

Dyn::Dyn() : 
	name("Kiwi")
{
	std::cout << "Kiwi" << std::endl;
}

Dyn::~Dyn()
{
	std::cout << "Karibou" << std::endl;
}

void Dyn::init()
{

	std::cout << "Init Dyn" << std::endl;
}

void Dyn::stop()
{
	std::cout << "Stop Dyn" << std::endl;
}

const std::string &Dyn::getName() const
{
	return name;
}