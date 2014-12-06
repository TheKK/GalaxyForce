/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: turrent.h
 */

#ifndef TURRENT_H
#define TURRENT_H

#include <SDL.h>
#include <vector>
#include <cmath>

#include "window.h"
#include "texture.h"
#include "turrentBullet.h"

class Turrent
{
public:
	Turrent();
	~Turrent();

	void eventHandler(const SDL_Event& event);
	void update(int mousePosX, int mousePosY);
	void render();

	void setPos(int x, int y);
	void setRotateDegree(double degree);

	void shootBullet();
private:
	Texture bodyPic_;
	Texture gunPic_;

	std::vector<Bullet*> bulletList_;

	SDL_Rect posRect_ = {0};
	SDL_Point rotateCenter_ = {0};

	double gunRotateDegree_;

	void updateBullets_();
	void renderBullets_();
};

#endif /* TURRENT_H */
