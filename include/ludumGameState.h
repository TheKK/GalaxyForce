/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: ludumGameState.h
 */

#ifndef LUDUM_GAME_STATE_H
#define LUDUM_GAME_STATE_H

#include <iostream>
#include <jsoncpp/json/json.h>
#include <vector>
#include <SDL.h>

#include "gameState.h"
#include "texture.h"
#include "turrent.h"
#include "normalSpaceShip.h"
#include "window.h"

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

	vector <SpaceShipBase*> spaceShipList_;
	vector <Bullet*> bulletList_;

	Texture backgroundPic_;

	int mousePosX_;
	int mousePosY_;

	void addNewSpaceShip_();
	void updateSpaceShips_();

	bool checkCallision_(SpaceShipBase* ship, Bullet* bullet);

	void updaetBullets_();
};

#endif /* LUDUM_GAME_STATE_H */
