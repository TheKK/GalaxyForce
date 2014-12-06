/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: stateMachine.h
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <SDL.h>

#include "gameActor.h"
#include "gameActorController.h"

class StateMachine
{
public:
	virtual ~StateMachine() {};

	virtual void bindActor(const GameActor& actor) = 0;
	virtual void bindController(const GameActorController& controller) = 0;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void handleInput() = 0;
	virtual void update() = 0;
};

#endif /* STATE_MACHINE_H */
