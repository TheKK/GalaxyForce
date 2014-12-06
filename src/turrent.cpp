/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrent.cpp
 */

#include "turrent.h"

Turrent::Turrent():
	bodyPic_("game/images/turrent_body.png", Window::renderer()),
	gunPic_("game/images/turrent_gun.png", Window::renderer())
{
	posRect_.x = 30;
	posRect_.y = 30;
	posRect_.w = 20;
	posRect_.h = 20;

	rotateCenter_.x = posRect_.w / 2;
	rotateCenter_.y = posRect_.h;
}

Turrent::~Turrent()
{
}

void
Turrent::eventHandler(const SDL_Event& event)
{
}

void
Turrent::update(int mousePosX, int mousePosY)
{
	double dx, dy;
	double GunRotateDegree;
	
	dx = mousePosX - (posRect_.x + rotateCenter_.x);
	dy = mousePosY - (posRect_.y + rotateCenter_.y);

	GunRotateDegree =
		(90.0 + (double) (180.0 / 3.14) * std::atan(dy / dx));

	if (dx < 0)
		GunRotateDegree += 180;

	gunPic_.rotateTo(GunRotateDegree);
}

void
Turrent::render()
{
	gunPic_.renderEx(posRect_, &rotateCenter_);
	bodyPic_.renderEx(posRect_, &rotateCenter_);
}
