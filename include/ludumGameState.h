/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: ludumGameState.h
 */

#ifndef LUDUM_GAME_STATE_H
#define LUDUM_GAME_STATE_H

#include <iostream>
#include <jsoncpp/json/json.h>
#include <SDL.h>

#include "gameState.h"
#include "texture.h"
#include "turrent.h"
#include "window.h"

using namespace std;

class LudumGameState : public GameState
{
public:
	LudumGameState();
	~LudumGameState();

	void eventHandler(const SDL_Event& event);
	void update();
	void render();
private:
	Turrent* turrentList_[5];

	Turrent turrent0_;
	Turrent turrent1_;
	Turrent turrent2_;
	Turrent turrent3_;
	Turrent turrent4_;

	Texture backgroundPic_;

	int mousePosX_;
	int mousePosY_;
};

#endif /* LUDUM_GAME_STATE_H */
