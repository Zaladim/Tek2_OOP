/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** SDL texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Texture {
	public:
		Texture();
		~Texture();

		//Loads image at specified path
		bool loadFromFile(std::string path, SDL_Renderer *renderer);
		bool loadFromText(TTF_Font *font, std::string text, SDL_Color color, SDL_Renderer *renderer);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);
		
		//Renders texture at given point
		void render(SDL_Renderer *renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	protected:
	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif /* !TEXTURE_HPP_ */
