/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrent.cpp
 */

#include "turrent.h"

Turrent::Turrent():
	bodyPic_("game/images/turrent_body.png", Window::renderer()),
	gunPic_("game/images/turrent_gun.png", Window::renderer()),
	cautionPic_("./game/images/turrent_edgeCaution.png", Window::renderer())
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
}

Turrent::~Turrent()
{
}

void
Turrent::eventHandler(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
			readyToShootBullet = true;
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

	if (gunRotateDegree_ > rotateEdgeRight) {
		gunRotateDegree_ = rotateEdgeRight;
		isOnEdge_ = true;
	} else if (gunRotateDegree_ <  rotateEdgeLeft) {
		gunRotateDegree_ = rotateEdgeLeft;
		isOnEdge_ = true;
	} else {
		isOnEdge_ = false;
	}

	normalizeDegree_(&gunRotateDegree_);

	gunPic_.rotateTo(gunRotateDegree_);

	if (readyToShootBullet) {
		shootBullet_(bulletList_);
		readyToShootBullet = false;
	}
}

void
Turrent::render()
{
	gunPic_.renderEx(bodyPosRect_, &rotateCenter_);
	bodyPic_.renderEx(bodyPosRect_, &rotateCenter_);

	if (isOnEdge_)
		cautionPic_.render(bodyPosRect_);
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
	Bullet* bullet = new TurrentBullet(
		bodyPosRect_.x + rotateCenter_.x, bodyPosRect_.y + rotateCenter_.y,
		gunRotateDegree_
		);

	bulletList->push_back(bullet);
}
