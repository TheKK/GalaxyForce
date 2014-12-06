/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrent.h
 */

#ifndef TURRENT_H
#define TURRENT_H

#include <iostream>
#include <SDL.h>

#include "window.h"
#include "texture.h"

using namespace std;

class Turrent
{
public:
	Turrent();
	~Turrent();

	void eventHandler(SDL_Event& event);
	void update(int mousePosX, int mousePosY);
	void render();

	void setTurrentCenter(int x, int y);
	void setRotateDegree(int n);
private:
	Texture bodyPic;
	Texture gunPic;

	SDL_Rect posRect = {0};
	SDL_Point posCenter = {0};
	int rotateDegree = 0;
};

#endif /* TURRENT_H */
