/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: smallSpaceShip.h
 */

#ifndef SMALL_SPACE_SHIP_H
#define SMALL_SPACE_SHIP_H

#include "window.h"
#include "spaceShipBase.h"
#include "sprite.h"
#include "sound.h"

class SmallSpaceShip : public SpaceShipBase
{
public:
	SmallSpaceShip(int startX, int startY);
	~SmallSpaceShip();

	void eventHandler(const SDL_Event& event);
	void update();
	void render();

	const SDL_Rect* rect() const;
private:
	Sprite shipSprite_;
	Sprite boomSprite_;

	static Sound boomSound_;
	ALuint source_;

	SDL_Rect posRect_ = {0};

	int moveDelay_ = 0;
	int shipSpriteDelay_ = 0;
	int boomSpriteDelay_ = 0;
};

#endif /* SMALL_SPACE_SHIP_H */
