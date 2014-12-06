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
	posRect_.x = 0;
	posRect_.y = 0;
	posRect_.w = 20;
	posRect_.h = 20;

	rotateCenter_.x = posRect_.w / 2;
	rotateCenter_.y = posRect_.h;

	bulletList_.resize(0);
}

Turrent::~Turrent()
{
	for (auto e : bulletList_) {
		delete e;
		e = nullptr;
	}

	bulletList_.clear();
}

void
Turrent::eventHandler(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
			shootBullet();
		break;
	}
}

void
Turrent::update(int mousePosX, int mousePosY)
{
	double dx, dy;
	
	dx = mousePosX - (posRect_.x + rotateCenter_.x);
	dy = mousePosY - (posRect_.y + rotateCenter_.y);

	gunRotateDegree_ =
		(double) (180.0 / 3.14) * std::atan(dy / dx);

	if (dx < 0)
		gunRotateDegree_ += 180;

	gunPic_.rotateTo(gunRotateDegree_ + 90);

	updateBullets_();
}

void
Turrent::render()
{
	renderBullets_();

	gunPic_.renderEx(posRect_, &rotateCenter_);
	bodyPic_.renderEx(posRect_, &rotateCenter_);
}

void
Turrent::setPos(int x, int y)
{
	posRect_.x = x;
	posRect_.y = y;
}

void
Turrent::setRotateDegree(double degree)
{
	bodyPic_.rotateTo(degree);

	gunRotateDegree_ = degree;
}

void
Turrent::shootBullet()
{
	Bullet* bullet = new TurrentBullet(
		posRect_.x + rotateCenter_.x, posRect_.y + rotateCenter_.y,
		gunRotateDegree_
		);

	bulletList_.push_back(bullet);
}

void
Turrent::updateBullets_()
{
	for (auto e : bulletList_)
		e->update();
}

void
Turrent::renderBullets_()
{
	for (auto e : bulletList_)
		e->render();
}
