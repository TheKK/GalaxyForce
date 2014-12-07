/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: spaceShipBase.h
 */

#ifndef SPACE_SHIP_BASE_H
#define SPACE_SHIP_BASE_H

#include <iostream>
#include <SDL.h>

#include "sound.h"

enum ShipState {
	STATE_NORMAL,
	STATE_BOOM,
	STATE_DEAD
};

class SpaceShipBase
{
public:
	SpaceShipBase()	{ std::cout << ++count_<< "\n";	};
	virtual ~SpaceShipBase() { std::cout << --count_<< "\n"; };

	virtual void eventHandler(const SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual const SDL_Rect* rect() const = 0;

	virtual void gotHit();

	void suicide();
	bool isDead() const;
protected:
	enum ShipState shipState_ = STATE_NORMAL;

	int hp_;
private:
	static int count_;
};

#endif /* SPACE_SHIP_BASE_H */
