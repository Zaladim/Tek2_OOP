/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Procedural level generation
*/

#include "Directories.hpp"
#define SAVE "save" 
 
void read_directory(const std::string& name, std::vector<std::string>& v)
{
    boost::filesystem::path p(name);
    if (!boost::filesystem::exists(name)){
        boost::filesystem::create_directory(p);
    }
    boost::filesystem::directory_iterator start(p);
    boost::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(v), path_string());
}

std::string getTexture(const char *textureName) {
	boost::filesystem::path p("assets");

	if (boost::filesystem::exists(p)) {
		for (auto& x : boost::filesystem::directory_iterator(p)) {
			if (x.path().filename() == textureName) {
				return x.path().string();
			}
		}
	}
	return ("");
}

std::string getFont(const char *fontName) {
	boost::filesystem::path p("assets");

	if (boost::filesystem::exists(p)) {
		for (auto& x : boost::filesystem::directory_iterator(p)) {
			if (x.path().filename() == fontName) {
				return x.path().string();
			}
		}
	}
	return ("");
}