/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameActor_Zup.cpp
 */

#include "gameActor_Zup.h"

#include "potionBullet.h"

GameActor_Zup::GameActor_Zup(const GameActorController& controller):
	sprite_onGround_("./game/images/zup_onGround.png", Window::renderer(),
			 30, 65),
	sprite_normalAttack_("./game/images/zup_normalAttack.png",
			     Window::renderer(), 30, 65),
	sprite_jumping_("./game/images/zup_jumping.png", Window::renderer(),
			30, 65),

	//stateMachine_("./game/scripts/character/Zup/states.lua"),

	frictionDelay_(0),
	gravityDelay_(0),
	spriteDelay_(0)
{
	stateMachine_ =
		new LuaStateMachine("./game/scripts/character/Zup/states.lua");
	stateMachine_->bindActor(*this);
	stateMachine_->bindController(controller);

	pos_.setRect(0, 0, 30, 65);

	gravity_ = 1;
	horizon_ = Window::height() - 70;

	spriteList_[SPRITE_ON_GROUND] = &sprite_onGround_;
	spriteList_[SPRITE_NORMAL_ATTACK] = &sprite_normalAttack_;
	spriteList_[SPRITE_JUMPING] = &sprite_jumping_;
	currentSprite_ = spriteList_[SPRITE_ON_GROUND];

	stateMachine_->onEnter();
}

GameActor_Zup::~GameActor_Zup()
{
}

void
GameActor_Zup::handleInput()
{
	stateMachine_->handleInput();
}

void
GameActor_Zup::update()
{
	handleInput();
	updateSprite();
	updatePosition();
	updateBullet(*this);

	stateMachine_->update();
}

void
GameActor_Zup::render()
{
	if (direction_ == FACE_RIGHT)
		currentSprite_->setFlip(FLIP_NONE);
	else
		currentSprite_->setFlip(FLIP_HORIZONTAL);

	currentSprite_->render(pos_.rect());

	renderBullet();
}

void
GameActor_Zup::updateSprite()
{
	if (++spriteDelay_ == 10) {
		currentSprite_->nextFrame();
		spriteDelay_ = 0;
	}
}

void
GameActor_Zup::updatePosition()
{
	pos_.moveBy(velX_, velY_);

	if ((!isOnGround()) && (++gravityDelay_ == 2)) {
		velY_ += gravity_;
		gravityDelay_ = 0;
	}

	if (pos_.y() + pos_.h() > horizon_)
		pos_.setY(horizon_ - pos_.h());

	if (velX_ != 0) {
		if (++frictionDelay_ == 4) {
			velX_ -= velX_ * 0.5;
			frictionDelay_ = 0;
		}
	}
}

void
GameActor_Zup::moveRight()
{
	applyAcc(1, 0);
	direction_ = FACE_RIGHT;
}

void
GameActor_Zup::moveLeft()
{
	applyAcc(-1, 0);
	direction_ = FACE_LEFT;
}

void
GameActor_Zup::normalAttack()
{
	addBullet(new PotionBullet(*this));
}
