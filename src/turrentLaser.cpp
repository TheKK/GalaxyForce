/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrentLaser.cpp
 */

#include "turrentLaser.h"

TurrentLaser::TurrentLaser(int startX, int startY, double degree):
	bulletPic_("./game/images/laser.png", Window::renderer())
{
	posRect_.w = 200;
	posRect_.h = 4;

	vX_ = moveSpeed_ * std::cos(degree * (3.14 / 180.0));
	vY_ = moveSpeed_ * std::sin(degree * (3.14 / 180.0));
	bulletPic_.rotateTo((180.0 / 3.14) * std::atan2(vY_, vX_));

	posRect_.x = startX - (posRect_.w / 2);
	posRect_.y = startY - (posRect_.h / 2);

	posX_ = posRect_.x;
	posY_ = posRect_.y;
}

TurrentLaser::~TurrentLaser()
{
}

void
TurrentLaser::update()
{
	posX_ += vX_;
	posY_ += vY_;

	posRect_.x = posX_;
	posRect_.y = posY_;

	if (SDL_HasIntersection(&posRect_, Window::rect()) == SDL_FALSE)
		suicide();
}

void
TurrentLaser::render()
{
	bulletPic_.renderEx(posRect_);
}
