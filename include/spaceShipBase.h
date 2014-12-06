/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: spaceShipBase.h
 */

#ifndef SPACE_SHIP_BASE_H
#define SPACE_SHIP_BASE_H

#include <iostream>
#include <SDL.h>

class SpaceShipBase
{
public:
	SpaceShipBase() {};
	virtual ~SpaceShipBase() {};

	virtual void eventHandler(const SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif /* SPACE_SHIP_BASE_H */
