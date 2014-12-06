/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: nromalSpaceShip.cpp
 */

#include "normalSpaceShip.h"

Sound NormalSpaceShip::boomSound_;

NormalSpaceShip::NormalSpaceShip(int startX, int startY):
	shipSprite_("./game/images/normalSpaceShip.png", Window::renderer(),
		    40, 20),
	boomSprite_("./game/images/normalSpaceShip_explode.png",
		    Window::renderer(),
		    40, 20)
{
	posRect_.x = startX;
	posRect_.y = startY;
	posRect_.w = 40;
	posRect_.h = 20;

	if (!boomSound_.hasLoaded())
		boomSound_.LoadSoundFile(
			"./game/sounds/normalSpaceShipBoom.ogg");

	source_ = boomSound_.requestSource();
}

NormalSpaceShip::~NormalSpaceShip()
{
	alDeleteSources(1, &source_);
}

void
NormalSpaceShip::eventHandler(const SDL_Event& event)
{
}

void
NormalSpaceShip::update()
{
	if (isHit()) {
		if (!Sound::isPlaying(source_))
			alSourcePlay(source_);

		if (boomSpriteDelay_++ == 5) {
			if (boomSprite_.nextFrame())
				suicide();
			boomSpriteDelay_ = 0;
		}
	} else {
		if (shipSpriteDelay_++ == 3) {
			shipSprite_.nextFrame();
			shipSpriteDelay_ = 0;
		}

		if (moveDelay_++ == 1) {
			posRect_.x += 3;
			moveDelay_ = 0;
		}
	}
}

void
NormalSpaceShip::render()
{
	if (isHit()) {
		boomSprite_.render(posRect_);
	} else {
		shipSprite_.render(posRect_);
	}
}

const SDL_Rect*
NormalSpaceShip::rect() const
{
	return &posRect_;
}
