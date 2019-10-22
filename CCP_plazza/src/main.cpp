/*
** EPITECH PROJECT, 2019
** 
** File description:
** 
*/

#include <iostream>
#include "Plazza.hpp"
#include "Reception.hpp"

int main(int argc, char **argv)
{
        if (argc != 4) {
                std::cerr<<"USAGE:\n\t./plazza [cooking time multiplier] [number of cooks per kitchen] [time in milliseconds]"<<std::endl;
                return (EXIT_ERROR);
        }
        Reception reception(atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
        reception.run();
        return (EXIT_SUCCESS);
}