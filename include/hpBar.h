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
#include "gameActor.h"

class HPBar
{
public:
	HPBar();
	~HPBar();

	void update();
	void render();

	void bindGameActor(const GameActor& actor);
private:
	Texture hpBar_;
	SDL_Rect posRect_ = {0};

	const GameActor* actor_;
};

#endif /* HP_BAR_H */
