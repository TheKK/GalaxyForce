/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: bullet.cpp
 */

#include "bullet.h"

int16_t
Bullet::damage() const
{
	return damage_;
}

void
Bullet::suicide()
{
	isDead_ = true;
}

bool
Bullet::isDead()
{
	return isDead_;
}

SDL_Rect*
Bullet::rect()
{
	return &posRect_;
}
