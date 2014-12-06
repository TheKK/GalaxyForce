/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: hpBar.h
 */

#ifndef HP_BAR_H
#define HP_BAR_H

#include <SDL.h>

#include "texture.h"
#include "window.h"

class HPBar
{
public:
	HPBar();
	~HPBar();

	void update();
	void render();

	void removeLife();
	void addLife();

	void resetLife();
private:
	Texture hpBar_;
	Texture life0_;
	Texture life1_;
	Texture life2_;

	SDL_Rect posRect_ = {0};

	int hp_ = 3;
};

#endif /* HP_BAR_H */
