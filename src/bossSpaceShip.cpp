/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: bossSpaceShip.cpp
 */

#include "bossSpaceShip.h"

Sound BossSpaceShip::boomSound_;
Sound BossSpaceShip::hitSound_;

BossSpaceShip::BossSpaceShip(int startX, int startY):
	shipSprite_("./game/images/bossSpaceShip.png", Window::renderer(),
		    100, 150),
	boomSprite_("./game/images/bossSpaceShip_explode.png",
		    Window::renderer(),
		    100, 150)
{
	posRect_.x = startX;
	posRect_.y = startY;
	posRect_.w = 100;
	posRect_.h = 150;

	hp_ = 30;

	if (!boomSound_.hasLoaded())
		boomSound_.LoadSoundFile(
			"./game/sounds/bossSpaceShipBoom.ogg");

	if (!hitSound_.hasLoaded())
		hitSound_.LoadSoundFile(
			"./game/sounds/bossSpaceShipHit.ogg");

	boomSource_ = boomSound_.requestSource();
	hitSource_ = hitSound_.requestSource();
}

BossSpaceShip::~BossSpaceShip()
{
	alDeleteSources(1, &boomSource_);
	alDeleteSources(1, &hitSource_);
}

void
BossSpaceShip::eventHandler(const SDL_Event& event)
{
}

void
BossSpaceShip::update()
{
	SDL_Rect interRect;

	switch (shipState_) {
	case STATE_NORMAL:
		if (shipSpriteDelay_++ == 3) {
			shipSprite_.nextFrame();
			shipSpriteDelay_ = 0;
		}

		if (moveDelay_++ == 3) {
			posRect_.x += 1;
			posRect_.y += vY_;
			SDL_IntersectRect(&posRect_, Window::rect(),
						 &interRect);
			if (!SDL_RectEquals(&posRect_, &interRect))
				vY_ *= -1;
			moveDelay_ = 0;
		}
		break;

	case STATE_BOOM:
		if (!Sound::isPlaying(boomSource_))
			alSourcePlay(boomSource_);

		if (boomSpriteDelay_++ == 5) {
			if (boomSprite_.nextFrame())
				suicide();
			boomSpriteDelay_ = 0;
		}
		break;

	case STATE_DEAD:
		break;
	}
}

void
BossSpaceShip::render()
{
	switch (shipState_) {
	case STATE_NORMAL:
		shipSprite_.render(posRect_);
		break;

	case STATE_BOOM:
		boomSprite_.render(posRect_);
		break;

	case STATE_DEAD:
		break;
	}
}

void
BossSpaceShip::gotHit()
{
	hp_--;
	if (hp_ == 0)
		shipState_ = STATE_BOOM;

	if (!Sound::isPlaying(boomSource_))
		alSourcePlay(hitSource_);
}

const SDL_Rect*
BossSpaceShip::rect() const
{
	return &posRect_;
}
