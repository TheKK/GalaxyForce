/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrent.cpp
 */

#include "turrent.h"

Sound Turrent::shootSound_;

Turrent::Turrent():
	bodyPic_("game/images/turrent_body.png", Window::renderer()),
	gunPic_("game/images/turrent_gun.png", Window::renderer())
{
	bodyPosRect_.x = 0;
	bodyPosRect_.y = 0;
	bodyPosRect_.w = 20;
	bodyPosRect_.h = 20;

	rotateCenter_.x = 0;
	rotateCenter_.y = bodyPosRect_.h / 2;

	cautionSignPosRect_.x = bodyPosRect_.x;
	cautionSignPosRect_.y = bodyPosRect_.y - bodyPosRect_.h;
	cautionSignPosRect_.w = 20;
	cautionSignPosRect_.h = 20;

	if (!shootSound_.hasLoaded())
		shootSound_.LoadSoundFile("./game/sounds/shoot.ogg");
}

Turrent::~Turrent()
{
}

void
Turrent::eventHandler(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (reloadDelay_ == 0)
				readyToShootBullet_ = true;
		}
		break;
	}
}

void
Turrent::update(int mousePosX, int mousePosY, vector<Bullet*>* bulletList_)
{
	double dx, dy;
	double rotateEdgeRight;
	double rotateEdgeLeft;

	dx = mousePosX - (bodyPosRect_.x + rotateCenter_.x);
	dy = mousePosY - (bodyPosRect_.y + rotateCenter_.y);

	rotateEdgeRight = bodyRotateDegree_ + maxRotatedegree_;
	rotateEdgeLeft = bodyRotateDegree_ - maxRotatedegree_;
	normalizeDegree_(&rotateEdgeRight);
	normalizeDegree_(&rotateEdgeLeft);

	gunRotateDegree_ =
		(double) (180.0 / 3.14) * std::atan2(dy,  dx);

	normalizeDegree_(&gunRotateDegree_);

	if (gunRotateDegree_ > rotateEdgeRight)
		gunRotateDegree_ = rotateEdgeRight;
	else if (gunRotateDegree_ <  rotateEdgeLeft)
		gunRotateDegree_ = rotateEdgeLeft;

	normalizeDegree_(&gunRotateDegree_);

	gunPic_.rotateTo(gunRotateDegree_);

	if (reloadDelay_ > 0)
		reloadDelay_--;

	if (readyToShootBullet_) {
		shootBullet_(bulletList_);
		readyToShootBullet_ = false;
		reloadDelay_ = 10;
	}
}

void
Turrent::render()
{
	gunPic_.renderEx(bodyPosRect_, &rotateCenter_);
	bodyPic_.renderEx(bodyPosRect_, &rotateCenter_);
}

void
Turrent::setPos(int x, int y)
{
	bodyPosRect_.x = x;
	bodyPosRect_.y = y;

	cautionSignPosRect_.x = bodyPosRect_.x;
	cautionSignPosRect_.y = bodyPosRect_.y;
}

void
Turrent::setRotateDegree(double degree)
{
	bodyRotateDegree_ = degree;
	normalizeDegree_(&bodyRotateDegree_);

	bodyPic_.rotateTo(bodyRotateDegree_);
}

void
Turrent::normalizeDegree_(double* n)
{
	/* Make sure n is positive */
	while (*n < 0)
		*n += 360;

	while (*n > 360)
		*n -= 360;
}

void
Turrent::shootBullet_(vector<Bullet*>* bulletList)
{
	Bullet* bullet;

	switch (bulletType_) {
	case BULLET_NORMAL:
		bullet = new TurrentBullet(
			bodyPosRect_.x + rotateCenter_.x,
			bodyPosRect_.y + rotateCenter_.y,
			gunRotateDegree_);
		bulletList->push_back(bullet);
		break;
	case BULLET_LASER:
		bullet = new TurrentLaser(
			bodyPosRect_.x + rotateCenter_.x,
			bodyPosRect_.y + rotateCenter_.y,
			gunRotateDegree_);
		bulletList->push_back(bullet);
		break;
	case BULLET_RAPID:
		for (int i = 0; i < 5; i ++) {
			bullet = new TurrentBullet(
				bodyPosRect_.x + rotateCenter_.x,
				bodyPosRect_.y + rotateCenter_.y,
				gunRotateDegree_);
			bulletList->push_back(bullet);
		}
		break;
	}

	shootSound_.Play();
}
