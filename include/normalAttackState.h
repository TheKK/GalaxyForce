/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: normalAttackState.h
 */

#ifndef NORMAL_ATTACK_STATE_H
#define NORMAL_ATTACK_STATE_H

#include "state.h"
#include "gameActor.h"
#include "gameActorController.h"
#include "potionBullet.h"

class NormalAttackState : public State
{
public:
	~NormalAttackState() {};

	void onEnter(GameActor& actor);
	void onExit(GameActor& actor);

	void handleInput(GameActor& actor,
			 const GameActorController& controller);
	void update(GameActor& actor);
private:
	int frameCount;
};

#endif /* NORMAL_ATTACK_STATE_H */
