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

class SpaceShipBase
{
public:
	SpaceShipBase()	{ std::cout << ++count_<< "\n";	};
	virtual ~SpaceShipBase() { std::cout << --count_<< "\n"; };

	virtual void eventHandler(const SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual const SDL_Rect* rect() const = 0;

	void gotHit();
	bool isHit() const;

	void suicide();
	bool isDead() const;
private:
	bool isHitten_ = false;
	bool isDead_ = false;

	static int count_;
};

#endif /* SPACE_SHIP_BASE_H */
