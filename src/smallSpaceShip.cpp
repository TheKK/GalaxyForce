/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: smallSpaceShip.cpp
 */

#include "smallSpaceShip.h"

Sound SmallSpaceShip::boomSound_;

SmallSpaceShip::SmallSpaceShip(int startX, int startY):
	shipSprite_("./game/images/smallSpaceship.png", Window::renderer(),
		    20, 20),
	boomSprite_("./game/images/smallSpaceship_explode.png",
		    Window::renderer(),
		    20, 20)
{
	posRect_.x = startX;
	posRect_.y = startY;
	posRect_.w = 20;
	posRect_.h = 20;

	hp_ = 2;

	if (!boomSound_.hasLoaded())
		boomSound_.LoadSoundFile(
			"./game/sounds/smallSpaceShipBoom.ogg");

	source_ = boomSound_.requestSource();
}

SmallSpaceShip::~SmallSpaceShip()
{
	alDeleteSources(1, &source_);
}

void
SmallSpaceShip::eventHandler(const SDL_Event& event)
{
}

void
SmallSpaceShip::update()
{
	switch (shipState_) {
	case STATE_NORMAL:
		if (shipSpriteDelay_++ == 3) {
			shipSprite_.nextFrame();
			shipSpriteDelay_ = 0;
		}

		if (moveDelay_++ == 1) {
			posRect_.x += 3;
			posRect_.y += 8 * std::sin(degree_);
			degree_ += 0.1;
			moveDelay_ = 0;
		}
		break;

	case STATE_BOOM:
		if (!Sound::isPlaying(source_))
			alSourcePlay(source_);

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
SmallSpaceShip::render()
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

const SDL_Rect*
SmallSpaceShip::rect() const
{
	return &posRect_;
}
