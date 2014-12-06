/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrent.cpp
 */

#include "turrent.h"

Turrent::Turrent():
	bodyPic("game/images/turrent_body.png", Window::renderer()),
	gunPic("game/images/turrent_gun.png", Window::renderer())
{
	posRect.x = 30;
	posRect.y = 30;
	posRect.w = 20;
	posRect.h = 20;
}

Turrent::~Turrent()
{
}

void
Turrent::eventHandler(SDL_Event& event)
{
}

void
Turrent::update(int mousePosX, int mousePosY)
{
	static int delay = 0;

	if (++delay == 5) {
		gunPic.rotate(10);
		bodyPic.rotate(10);
		delay = 0;
	}
}

void
Turrent::render()
{
	SDL_Point p;
	p.x = posRect.w / 2;
	p.y = posRect.h;

	gunPic.renderEx(posRect, &p);
	bodyPic.renderEx(posRect, &p);
}
