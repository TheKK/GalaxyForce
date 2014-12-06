/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: nromalSpaceShip.cpp
 */

#include "normalSpaceShip.h"

NormalSpaceShip::NormalSpaceShip(int startX, int startY):
	shipPic_("./game/images/normalSpaceShip.png", Window::renderer())
{
	posRect_.x = startX;
	posRect_.y = startY;
	posRect_.w = 40;
	posRect_.h = 20;
}

NormalSpaceShip::~NormalSpaceShip()
{
}

void
NormalSpaceShip::eventHandler(const SDL_Event& event)
{
}

void
NormalSpaceShip::update()
{
	SDL_Rect windowRect = Window::rect();

	if (moveDelay_++ == 1) {
		posRect_.x += 5;
		moveDelay_ = 0;
	}

	if (!SDL_HasIntersection(&posRect_, &windowRect))
		suicide();
}

void
NormalSpaceShip::render()
{
	shipPic_.render(posRect_);
}

const SDL_Rect*
NormalSpaceShip::rect() const
{
	return &posRect_;
}
