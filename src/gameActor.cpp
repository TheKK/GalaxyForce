/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameActor.cpp
 */

#include "gameActor.h"

GameActor::GameActor()
{
	spriteList_.resize(SPRITE_COUNT);
}

GameActor::~GameActor()
{
	for (auto e : bulletList_)
		delete e;

	bulletList_.clear();

	if (stateMachine_)
		delete stateMachine_;
	stateMachine_ = nullptr;
}

int16_t
GameActor::hp() const
{
	return hp_;
}

void
GameActor::applyAcc(int accX, int accY)
{
	velX_ += accX;
	velY_ += accY;
}

void
GameActor::setVelX(int n)
{
	velX_ = n;
}

void
GameActor::setVelY(int n)
{
	velY_ = n;
}

int
GameActor::velX() const
{
	return velX_;
}

int
GameActor::velY() const
{
	return velY_;
}

void
GameActor::setGravity(int g)
{
	gravity_ = g;
}

void
GameActor::setHorizon(int h)
{
	horizon_ = h;
}

int
GameActor::gravity() const
{
	return gravity_;
}

int
GameActor::horizon() const
{
	return horizon_;
}

bool
GameActor::isOnGround() const
{
	return (pos_.y() + pos_.h() >= horizon_);
}

enum FaceDirection
GameActor::direction() const
{
	return direction_;
}
void
GameActor::addBullet(Bullet* bullet)
{
	bulletList_.push_back(bullet);
}

const vector<Bullet*>&
GameActor::bulletList()
{
	return bulletList_;
}

void
GameActor::testBulletCollision(GameActor& caster)
{
	if (isInvisible_)
		return;

	for (Bullet* bullet : caster.bulletList()) {
		if (SDL_HasIntersection(&pos_.rect(), bullet->rect())) {
			hp_ -= bullet->damage();

			if (hp_ <= 0) {
				cout << "you die" << endl;
				bullet->suicide();
			} else {
				cout << "hp: " << hp_ << endl;
				bullet->suicide();
			}
		}
	}
}

void
GameActor::updateBullet(GameActor& target)
{
	for (auto bullet = bulletList_.rbegin();
	     bullet != bulletList_.rend();
	     bullet++) {

		(*bullet)->update(target);

		if ((*bullet)->isDead()) {
			delete (*bullet);
			bulletList_.erase(next(bullet).base());
		}
	}
}

void
GameActor::renderBullet()
{
	for (Bullet* bullet : bulletList_)
		bullet->render();
}

void
GameActor::setAsInvisible()
{
	isInvisible_ = true;
}

void
GameActor::setAsVisible()
{
	isInvisible_ = false;
}

bool
GameActor::isInvisible() const
{
	return isInvisible_;
}

const Position&
GameActor::pos() const
{
	return pos_;
}

void
GameActor::setSprite(enum ActorSprite which)
{
	SDL_assert(spriteList_[which] != nullptr);

	currentSprite_ = spriteList_[which];
	currentSprite_->jumpTo(0);
}
