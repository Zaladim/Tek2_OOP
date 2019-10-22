/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Sound class
*/

#include "Sound.hpp"

Sound::Sound()
{
	boost::filesystem::path p("assets");

	if (boost::filesystem::exists("assets")) {
		for (auto&& x : boost::filesystem::directory_iterator(p)) {
			if (x.path().extension() == ".wav") {
				_sounds.push_back(x.path().c_str());
			}
		}
	}
}

Sound::~Sound()
{
}

#include <thread>

int Sound::play(std::string soundFile)
{
	for (auto &file : _sounds) {
		if (file.compare(file.length() - soundFile.length(), soundFile.length(), soundFile) == 0) {
			soundFile = file;
			break;
		}
	}

	if (!_buffer.loadFromFile(soundFile)) {
		return -1;
	}
	_queue.push_back(sf::Sound(_buffer));
	_queue.back().play();


	for (int i = 0 ; i < _queue.size() ; ++i) {
		if (_queue[i].getStatus() == sf::Sound::Stopped)
		{
			_queue.erase(_queue.begin() + i);
			--i;
		}
	}
	return 0;

}

void Sound::stop()
{
	for (auto &elem : _queue) {
		elem.stop();
	}
	_queue.clear();
	_music.stop();
}

void Sound::music(std::string music)
{
	for (auto &file : _sounds) {
		if (file.compare(file.length() - music.length(), music.length(), music) == 0) {
			music = file;
			break;
		}
	}


	if (_music.openFromFile(music)) {
		_music.setLoop(true);
		_music.play();
	}
}
