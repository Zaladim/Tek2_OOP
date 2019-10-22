/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** sdl Texture
*/

#include "Texture.hpp"

Texture::Texture() : 
	mTexture(NULL),
	mWidth(0),
	mHeight(0)
{
}

Texture::~Texture()
{
	free();
}

#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

bool Texture::loadFromFile(std::string path, SDL_Renderer *renderer)
{
	free();

	std::string kiwi = fs::current_path().string();

	path = fs::current_path().string() + "/" + path;

	SDL_Texture *newTexture = NULL;

	SDL_Surface *surface = IMG_Load(path.c_str());
	if (surface == NULL){
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(renderer, surface);


	mWidth = surface->w;
	mHeight = surface->h;

	SDL_FreeSurface(surface);

	mTexture = newTexture;
	return mTexture != NULL;
}

bool Texture::loadFromText(TTF_Font *font, std::string text, SDL_Color color, SDL_Renderer *renderer)
{
	free();

	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (textSurface == NULL) {
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	} else {
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL) { 
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		} else {
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

void Texture::free()
{
	if (mTexture != NULL) {
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void Texture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Texture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight};
	
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}