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

	const vector<Bullet*>& bulletList() const;
private:
	Texture bodyPic_;
	Texture gunPic_;
	Texture cautionPic_;

	bool isOnEdge_ = false;

	std::vector<Bullet*> bulletList_;

	SDL_Rect bodyPosRect_ = {0};
	SDL_Rect cautionSignPosRect_ = {0};
	SDL_Point rotateCenter_ = {0};

	int cautionBlinkDelay_ = 0;

	const double maxRotatedegree_ = 50;
	double gunRotateDegree_ = 0;
	double bodyRotateDegree_ = 0;

	void updateBullets_();
	void renderBullets_();

	void normalizeDegree_(double* n);
};

#endif /* TURRENT_H */
