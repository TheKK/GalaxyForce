/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrent.h
 */

#ifndef TURRENT_H
#define TURRENT_H

#include <SDL.h>
#include <cmath>

#include "window.h"
#include "texture.h"
#include "bullet.h"

class Turrent
{
public:
	Turrent();
	~Turrent();

	void eventHandler(const SDL_Event& event);
	void update(int mousePosX, int mousePosY);
	void render();

	void setTurrentCenter(int x, int y);
	void setRotateDegree(int n);
private:
	Texture bodyPic_;
	Texture gunPic_;

	SDL_Rect posRect_ = {0};
	SDL_Point rotateCenter_ = {0};
};

#endif /* TURRENT_H */
