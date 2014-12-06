/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: potionBullet.h
 */

#ifndef POTION_BULLET_H
#define POTION_BULLET_H

#include <iostream>
#include <SDL.h>

#include "bullet.h"
#include "window.h"

using namespace std;

class PotionBullet : public Bullet
{
public:
	PotionBullet(GameActor& caster);
	~PotionBullet();

	void update(GameActor& target);
	void render();
private:
	int delay_;;
	int horizon_;
	int velX_;
	int velY_;
	int gravity_;
	bool isOnGround_();
};

#endif /* POTION_BULLET_H */

