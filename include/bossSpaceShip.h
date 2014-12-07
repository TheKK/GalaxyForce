/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: bossSpaceShip.h
 */

#ifndef BOSS_SPACE_SHIP_H
#define BOSS_SPACE_SHIP_H

#include "window.h"
#include "spaceShipBase.h"
#include "sprite.h"
#include "sound.h"

class BossSpaceShip : public SpaceShipBase
{
public:
	BossSpaceShip(int startX, int startY);
	~BossSpaceShip();

	void eventHandler(const SDL_Event& event);
	void update();
	void render();

	void gotHit();
	const SDL_Rect* rect() const;
private:
	Sprite shipSprite_;
	Sprite boomSprite_;

	static Sound boomSound_;
	ALuint boomSource_;

	static Sound hitSound_;
	ALuint hitSource_;

	SDL_Rect posRect_ = {0};

	int vY_ = rand() % 2 - 1;

	int moveDelay_ = 0;
	int shipSpriteDelay_ = 0;
	int boomSpriteDelay_ = 0;
};

#endif /* BOSS_SPACE_SHIP_H */
