/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: state.h
 */

#ifndef STATE_H
#define STATE_H

#include <lua.hpp>

#include "gameActor.h"
#include "gameActorController.h"

using namespace std;

class State
{
public:
	State()
	{

	};
	virtual ~State() {};

	virtual void onEnter(GameActor& actor) = 0;
	virtual void onExit(GameActor& actor) = 0;

	virtual void handleInput(GameActor& actor,
				 const GameActorController& controller) = 0;
	virtual void update(GameActor& actor) = 0;
};

#endif /* STATE_H */
