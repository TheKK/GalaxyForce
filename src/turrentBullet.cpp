/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrentBullet.h
 */

#include "turrentBullet.h"

TurrentBullet::TurrentBullet(int startX, int startY, double degree):
	bulletPic_("./game/images/turrentBullet.png", Window::renderer())
{
	posRect_.w = 4;
	posRect_.h = 4;

	posRect_.x = startX - (posRect_.w / 2);
	posRect_.y = startY - (posRect_.h / 2);

	posX_ = startX;
	posY_ = startY;

	vX_ = moveSpeed_ * std::cos(degree * (3.14 / 180.0));
	vY_ = moveSpeed_ * std::sin(degree * (3.14 / 180.0));
}

TurrentBullet::~TurrentBullet()
{
}

void
TurrentBullet::update()
{
	SDL_Rect windowRect = Window::rect();

	posX_ += vX_;
	posY_ += vY_;

	posRect_.x = posX_;
	posRect_.y = posY_;

	if (SDL_HasIntersection(&posRect_, &windowRect) == SDL_TRUE)
		suicide();
}

void
TurrentBullet::render()
{
	bulletPic_.render(posRect_);
}
