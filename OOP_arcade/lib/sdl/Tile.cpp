/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** sdl Tile
*/

#include "Tile.hpp"

Tile::Tile(int x, int y, int tileType) : 
	mType(tileType)
{
	// offsets
	mBox.x = x;
	mBox.y = y;

	//Collision
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;
}

Tile::~Tile()
{
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

void Tile::render(SDL_Renderer *renderer, Texture *TileTexture, SDL_DisplayMode dm, SDL_Rect *tileClips, std::size_t boardW, std::size_t boardH)
{
	TileTexture->render(renderer, mBox.x + (dm.w - boardW)/2, mBox.y + (dm.h - boardH)/2, &tileClips[mType]);
}