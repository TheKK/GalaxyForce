/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: onGroundState.cpp
 */

#include "onGroundState.h"

void
OnGroundState::onEnter(GameActor& actor)
{
}


void
OnGroundState::onExit(GameActor& actor)
{
}

void
OnGroundState::handleInput(GameActor& actor,
			   const GameActorController& controller)
{
	if (controller.getButtonState(BUTTON_RIGHT))
		actor.moveRight();

	if (controller.getButtonState(BUTTON_LEFT))
		actor.moveLeft();

	if (controller.ifButtonPressed(BUTTON_NORMAL_ATTACK))
		actor.normalAttack();

	if (controller.getButtonState(BUTTON_JUMP))
		actor.jump();
}

void
OnGroundState::update(GameActor& actor)
{
}
