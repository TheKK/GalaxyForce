/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: onGroundState.h
 */

#ifndef ON_GROUND_STATE_H
#define ON_GROUND_STATE_H

#include <lua.hpp>

#include "state.h"
#include "gameActor.h"
#include "gameActorController.h"

class OnGroundState : public State
{
public:
	~OnGroundState() {};

	void onEnter(GameActor& actor);
	void onExit(GameActor& actor);

	void handleInput(GameActor& actor,
			 const GameActorController& controller);
	void update(GameActor& actor);
};

#endif /* ON_GROUND_STATE_H */
