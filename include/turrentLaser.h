/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrentLaser.h
 */

#ifndef TURRENT_LASER_CPP
#define TURRENT_LASER_CPP

#include <iostream>
#include <cmath>
#include <SDL.h>

#include "window.h"
#include "bullet.h"
#include "texture.h"

class TurrentLaser : public Bullet
{
public:
	TurrentLaser(int startX, int startY, double degree);
	~TurrentLaser();

	void update();
	void render();

private:
	Texture bulletPic_;

	const double moveSpeed_ = 6.0f;

	double vX_, vY_;
	double posX_, posY_;
};

#endif /* TURRENT_LASER_CPP */
