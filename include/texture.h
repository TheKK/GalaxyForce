/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: texture.h
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "renderable.h"

using namespace std;

class Texture : public Renderable
{
public:
	Texture();
	Texture(const char* filePath, SDL_Renderer* renderer,
		Uint8 r = 0, Uint8 g = 255, Uint8 b = 255);
	~Texture();

	void load(const char* filePath, SDL_Renderer* renderer,
		  Uint8 r = 0, Uint8 g = 255, Uint8 b = 255);

	void rotateBy(double value);
	void rotateTo(double value);

	void setAlpha(Uint8 value);
	SDL_Texture* object() const;

	void setBlendMode(SDL_BlendMode mode);

	void render(const SDL_Rect& rect);

	/* Update this to class Renderable if you have free time */
	void renderEx(const SDL_Rect& rect, SDL_Point* rotateCenter = nullptr);
	void renderFullWindow();
private:
	SDL_Texture* texture_ = nullptr;

	double degree_ = 0;
	Uint8 alpha_ = SDL_ALPHA_OPAQUE;

	void release_();
};

#endif	/* TEXTURE_H */
