/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameActor_Zup.h
 */

#ifndef GAME_ACTOR_ZUP_H
#define GAME_ACTOR_ZUP_H

#include "gameActor.h"
#include "luaStateMachine.h"
#include "sprite.h"
#include "window.h"

class GameActor_Zup : public GameActor
{
public:
	GameActor_Zup(const GameActorController& controller);
	~GameActor_Zup();

	void handleInput();
	void update();
	void render();

	void updateSprite();
	void updatePosition();

	void moveRight();
	void moveLeft();
	void normalAttack();
private:
	Sprite sprite_onGround_;
	Sprite sprite_normalAttack_;
	Sprite sprite_jumping_;
	//Sprite sprite_jumpingAttack_;

	int frictionDelay_;
	int gravityDelay_;
	int spriteDelay_;
};

#endif /* GAME_ACTOR_ZUP_H */
