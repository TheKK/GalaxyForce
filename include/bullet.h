/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: bullet.h
 */

#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <SDL.h>

using namespace std;

class GameActor;

class Bullet
{
public:
	virtual ~Bullet() {};

	virtual void update() = 0;
	virtual void render() = 0;

	int16_t damage() const;

	void suicide();
	bool isDead();

	const SDL_Rect* rect() const;
protected:
	bool isDead_ = false;
	int16_t damage_;
	SDL_Rect posRect_;
};

#endif /* BULLET_H */

