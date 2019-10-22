/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Allegro lib
*/

#ifndef ALLEGRO_HPP_
#define ALLEGRO_HPP_

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_ttf.h>
#include "../ALib.hpp"

class Allegro : public ALib {
	public:
		Allegro();
		~Allegro();


		// === START ===
		int open(std::vector<std::string> libs);
		void close();
		int run(std::vector<std::string> libs, std::vector<std::vector<int>> board, int score);

		// === TEXT ===
		void printLib(std::vector<std::string> libs);
		void printScore(int score);
		void printName();
		int setName(ALLEGRO_EVENT_QUEUE *events);

		// === GAME ===
		void displayGame(std::vector<std::vector<int>> board);
		void displayPause();

	protected:
	private:
		ALLEGRO_DISPLAY *_main;
		ALLEGRO_DISPLAY_MODE _dm;
		ALLEGRO_TIMER *_timer;
		ALLEGRO_FONT *_font;

		bool _moving[4] = {false, false, false, false};

		enum DIR{
			UP, DOWN, LEFT, RIGHT
		};

		ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
   		ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
    	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
		ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
		ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
		ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
		ALLEGRO_COLOR purple = al_map_rgb(138, 43,226);

		std::string _libText;
		std::string _nameText;

		int _score;
};

#endif /* !ALLEGRO_HPP_ */
