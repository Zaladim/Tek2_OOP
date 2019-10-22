/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Sound class
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <deque>
#include <boost/filesystem.hpp>
#include "Directories.hpp"

#define MUSIC "Music.wav"
#define CLICK "Click.wav"
#define EXPL "Bomb.wav"
#define DEAD "Death.wav"
#define KILL "MonsterDeath.wav"

class Sound {
	public:
		Sound();
		~Sound();

		int play(std::string soundFile);
		void stop();
		void music(std::string music);

	protected:
	private:
		bool _playing = true;
		std::vector<std::string> _sounds;

		sf::SoundBuffer _buffer;

		std::deque<sf::Sound> _queue;
		sf::Music _music;
};

#endif /* !SOUND_HPP_ */
