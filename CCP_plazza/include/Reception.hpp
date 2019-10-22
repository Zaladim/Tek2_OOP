/*
** EPITECH PROJECT, 2019
** 
** File description:
** 
*/

#ifndef _RECEPTION_
#define _RECEPTION_

#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <filesystem>
#include <cmath>
#include "Plazza.hpp"
#include "Kitchen.hpp"
#include "Pipe.hpp"
#include "Pizza.hpp"

namespace fs = std::filesystem;

class Reception
{
    public:
        Reception(float multiplier_cooking_time, int cooks_per_kitchen, int time);
        ~Reception(void);

        void run();

    private:
        void welcome();
        void menu();
        void help();

        int do_command(std::vector<std::string> parameters);
        void status();
        void commandHandler(std::string &cmd); // Find or create a free kitchen and send a cmd
        void createKitchen(); // Create new kitchen and read/write pipe
        void selectKitchen(); // Ask all kitchen for nb of free cook, chose se least occupied one

		void cleanKitchen(); // Check if some kitchen have closed

        float _multiplier_cooking_time;
        int _cooks_per_kitchen;
        int _time;

        Pipe *_currentKitchen;
        std::vector<Pipe *> _kitchens;
};

#endif