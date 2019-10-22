/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Functions
*/

#include "Plazza.hpp"

std::vector<std::string> parser(std::string command, char cutter)
{
	std::vector<std::string> parameters;

	std::istringstream ss(command);
	std::string word;

	while (getline(ss, word, cutter)) {
		parameters.push_back(word);
	}
	return (parameters);
}
