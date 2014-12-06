/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: renderable.h
 */

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Renderable
{
public:
	Renderable();
	virtual ~Renderable();

	virtual void render(const SDL_Rect& rect) = 0;

	virtual void setAlpha(uint8_t value) = 0;

	SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer,
				 Uint8 r, Uint8 g, Uint8 b);

	void setRenderer(SDL_Renderer* renderer);

	void hide();
	void show();
	void setVisable(bool value);
	bool isVisable() const;
private:
	static uint32_t objectCount_;
protected:
	SDL_Renderer* targetRenderer_ = nullptr;
	bool visable_ = true;
};

#endif	/* RENDERABLE_H */
