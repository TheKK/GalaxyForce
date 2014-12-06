/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: testGameState.h
 */

#ifndef TEST_GAME_STATE_H
#define TEST_GAME_STATE_H

#include <iostream>
#include <SDL.h>

#include "gameState.h"
#include "gameActor_Zup.h"
#include "gameActorController.h"
#include "texture.h"
#include "hpBar.h"
#include "window.h"

using namespace std;

class TestGameState : public GameState
{
public:
	TestGameState();
	~TestGameState();

	void eventHandler(const SDL_Event& event);
	void update();
	void render();
private:
	GameActorController controller_;
	GameActorController controller2_;

	GameActor_Zup actor_;
	GameActor_Zup actor2_;

	HPBar boosHpBar_;

	Texture backGroundBG_;
	Texture backGroundFG_;
};

#endif /* TEST_GAME_STATE_H */
