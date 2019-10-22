/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** SDL tile
*/

#ifndef TILE_HPP_
#define TILE_HPP_

#include <SDL2/SDL.h>
#include "Texture.hpp"

//Tile constants 
const int TILE_WIDTH = 10; 
const int TILE_HEIGHT = 10; 
const int TOTAL_TILES = 192; 
const int TOTAL_TILE_SPRITES = 12; 

//The different tile sprites 
const int TILE_RED = 0; 
const int TILE_GREEN = 1; 
const int TILE_BLUE = 2; 
const int TILE_CENTER = 3; 
const int TILE_TOP = 4; 
const int TILE_TOPRIGHT = 5; 
const int TILE_RIGHT = 6; 
const int TILE_BOTTOMRIGHT = 7; 
const int TILE_BOTTOM = 8; 
const int TILE_BOTTOMLEFT = 9; 
const int TILE_LEFT = 10; 
const int TILE_TOPLEFT = 11;

class Tile {
	public:
		Tile(int x, int y, int tileType);
		~Tile();

		// === Get Tile type ===
		int getType();

		// === Get Collision box ===
		SDL_Rect getBox();

		// === Show Tile ===
		void render(SDL_Renderer *renderer, Texture *tileTexture, SDL_DisplayMode dm, SDL_Rect *tileClips, std::size_t boardW, std::size_t boardH);

	protected:
	private:
		// === Tile attributes ===
		SDL_Rect mBox;
		// === Tile type ===
		int mType;
};

#endif /* !TILE_HPP_ */
