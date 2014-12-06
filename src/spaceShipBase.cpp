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
	isHitten_ = true;
}

bool
SpaceShipBase::isHit() const
{
	return isHitten_;
}

void
SpaceShipBase::suicide()
{
	isDead_ = true;
}

bool
SpaceShipBase::isDead() const
{
	return isDead_;
}
