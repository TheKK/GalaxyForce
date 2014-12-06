/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrentBullet.h
 */

#ifndef TURRENT_BULLET_CPP
#define TURRENT_BULLET_CPP

#include <iostream>
#include <cmath>
#include <SDL.h>

#include "window.h"
#include "bullet.h"
#include "texture.h"

class TurrentBullet : public Bullet
{
public:
	TurrentBullet(int startX, int startY, double degree);
	~TurrentBullet();

	void update();
	void render();

private:
	Texture bulletPic_;

	const double moveSpeed_ = 3.0f;

	double vX_, vY_;
	double posX_, posY_;
};

#endif /* TURRENT_BULLET_CPP */
