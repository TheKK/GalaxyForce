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
#include "turrentLaser.h"
#include "sound.h"

enum BulletType {
	BULLET_NORMAL = 0x00,
	BULLET_LASER,
	BULLET_RAPID
};

class Turrent
{
public:
	Turrent();
	~Turrent();

	void eventHandler(const SDL_Event& event);
	void update(int mousePosX, int mousePosY, vector<Bullet*>* bulletList_);
	void render();

	void setPos(int x, int y);
	void setRotateDegree(double degree);
	void shootBullet_(vector<Bullet*>* bulletList_);
private:
	Texture bodyPic_;
	Texture gunPic_;

	static Sound shootSound_;

	enum BulletType bulletType_ = BULLET_NORMAL;

	bool readyToShootBullet_ = false;

	SDL_Rect bodyPosRect_ = {0};
	SDL_Rect cautionSignPosRect_ = {0};
	SDL_Point rotateCenter_ = {0};

	const double maxRotatedegree_ = 50;
	double gunRotateDegree_ = 0;
	double bodyRotateDegree_ = 0;

	int reloadDelay_ = 0;

	void normalizeDegree_(double* n);
};

#endif /* TURRENT_H */
