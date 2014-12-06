/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: potionBullet.cpp
 */

#include "potionBullet.h"

PotionBullet::PotionBullet(GameActor& caster)
{
	const Position& caster_pos = caster.pos();

	if (caster.direction() == FACE_RIGHT) {
		posRect_ ={(caster_pos.x() + 20), (caster_pos.y() + 10),
			10, 10};
		velX_ = 10 + caster.velX() * 1.5;
	} else {
		posRect_ = {(caster_pos.x() + caster_pos.w() - 30),
			(caster_pos.y() + 10), 10, 10};
		velX_ = -10 + caster.velX() * 1.5;
	}

	horizon_ = caster.horizon();
	delay_ = 0;

	velY_ = -10;
	gravity_ = 1;

	damage_ = 9;
}

PotionBullet::~PotionBullet()
{
}

void
PotionBullet::update(GameActor& target)
{
	if (!isOnGround_()) {
		velY_ += gravity_;

		posRect_.x += velX_;
		posRect_.y += velY_;
	} else {
		if (++delay_ == 30)
			suicide();
	}
}

void
PotionBullet::render()
{
	SDL_SetRenderDrawColor(Window::renderer(), 50, 100, 30, 255);
	SDL_RenderFillRect(Window::renderer(), &posRect_);
}

bool
PotionBullet::isOnGround_()
{
	return (posRect_.y + posRect_.h >= horizon_);
}
