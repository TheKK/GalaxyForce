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

	vX_ = moveSpeed_ * std::cos(degree * (3.14 / 180.0));
	vY_ = moveSpeed_ * std::sin(degree * (3.14 / 180.0));

	posRect_.x = startX - (posRect_.w / 2);
	posRect_.y = startY - (posRect_.h / 2);

	posX_ = posRect_.x;
	posY_ = posRect_.y;

	update();
	update();
	update();
	update();
	update();
}

TurrentBullet::~TurrentBullet()
{
}

void
TurrentBullet::update()
{
	posX_ += vX_;
	posY_ += vY_;

	posRect_.x = posX_;
	posRect_.y = posY_;

	if (SDL_HasIntersection(&posRect_, Window::rect()) == SDL_FALSE)
		suicide();
}

void
TurrentBullet::render()
{
	bulletPic_.render(posRect_);
}
