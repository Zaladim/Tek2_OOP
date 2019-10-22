/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Directories
*/

#ifndef DIRECTORIES_HPP_
#define DIRECTORIES_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>

struct path_string
{
    std::string operator()(const boost::filesystem::directory_entry& entry) const
    {
        return entry.path().string();
    }
};


void read_directory(const std::string& name, std::vector<std::string>& v);
std::string getTexture(const char *textureName);
std::string getFont(const char *fontName);

#endif /* !DIRECTORIES_HPP_ */
