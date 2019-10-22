/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** SDL lib
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include "../ALib.hpp"
#include "Tile.hpp"
#include "Texture.hpp"

class SDL : public ALib {
	public:
		SDL();
		~SDL();

		// === START ===
		int open(std::vector<std::string> libs) override;
		void close() override;
		int run(std::vector<std::string> libs, std::vector<std::vector<int>> board, int score) override;

		// === TEXT ===
		void printLib(std::vector<std::string> libs) override;
		void printScore(int score) override;
		void printName() override;
		int setName();

		// === GAME ===
		void displayGame(std::vector<std::vector<int>> board) override;
		void displayPause() override;
	protected:
	private:

		SDL_Window *_main;
		SDL_Renderer *_mainRenderer;
		SDL_DisplayMode _dm;
		TTF_Font *_font;
		SDL_Color _textColor;
		Texture _libs;
		Texture _scoring;
		Texture _name;

		std::string _textScore;
		std::string _playerName;
		int _score;
		bool _run;
};

#endif /* !SDL_HPP_ */
