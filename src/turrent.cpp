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

	updateBullets_();
}

void
Turrent::render()
{
	renderBullets_();

	gunPic_.renderEx(bodyPosRect_, &rotateCenter_);
	bodyPic_.renderEx(bodyPosRect_, &rotateCenter_);

	if (isOnEdge_ && ++cautionBlinkDelay_ == 5) {
		cautionPic_.render(bodyPosRect_);
		cautionBlinkDelay_ = 0;
	}
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
Turrent::shootBullet()
{
	Bullet* bullet = new TurrentBullet(
		bodyPosRect_.x + rotateCenter_.x, bodyPosRect_.y + rotateCenter_.y,
		gunRotateDegree_
		);

	bulletList_.push_back(bullet);
}

const vector<Bullet*>&
Turrent::bulletList() const
{
	return bulletList_;
}

void
Turrent::updateBullets_()
{
	for (auto bullet = bulletList_.rbegin();
	     bullet != bulletList_.rend();
	     bullet++) {

		(*bullet)->update();

		if ((*bullet)->isDead()) {
			delete (*bullet);
			bulletList_.erase(next(bullet).base());
		}
	}
}

void
Turrent::renderBullets_()
{
	for (auto e : bulletList_)
		e->render();
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
