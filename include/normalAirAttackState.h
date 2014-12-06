/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: normalAirAttackState.h
 */

#ifndef NORMAL_AIR__ATTACK_STATE_H
#define NORMAL_AIR__ATTACK_STATE_H

#include "state.h"
#include "gameActor.h"
#include "gameActorController.h"
#include "potionBullet.h"

class NormalAirAttackState : public State
{
public:
	~NormalAirAttackState() {};

	void onEnter(GameActor& actor);
	void onExit(GameActor& actor);

	void handleInput(GameActor& actor,
			 const GameActorController& controller);
	void update(GameActor& actor);
private:
	int frameCount;
};

#endif /* NORMAL_AIR__ATTACK_STATE_H */
