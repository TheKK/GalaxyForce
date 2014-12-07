/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: spaceShipBase.cpp
 */

#include "spaceShipBase.h"

int SpaceShipBase::count_ = 0;

void
SpaceShipBase::gotHit()
{
	hp_--;
	if (hp_ == 0)
		shipState_ = STATE_BOOM;
}

void
SpaceShipBase::suicide()
{
	shipState_ = STATE_DEAD;
}

bool
SpaceShipBase::isDead() const
{
	return (shipState_ == STATE_DEAD);
}
