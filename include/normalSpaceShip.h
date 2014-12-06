/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: nromalSpaceShip.h
 */

#ifndef NORMAL_SPACE_SHIP_H
#define NORMAL_SPACE_SHIP_H

#include "spaceShipBase.h"
#include "texture.h"

class NormalSpaceShip
{
public:
	NormalSpaceShip();
	~NormalSpaceShip();

	void eventHandler(const SDL_Event& event);
	void update();
	void render();
private:
	Texture shipPic_;
	SDL_Rect posRect_ = {0};
};

#endif /* NORMAL_SPACE_SHIP_H */
