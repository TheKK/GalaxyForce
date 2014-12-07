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
#include "smallSpaceShip.h"
#include "bossSpaceShip.h"
#include "hpBar.h"
#include "sound.h"
#include "window.h"
#include "title.h"
#include "gameover.h"
#include "gameClear.h"

enum GameStage {
	GAME_TITLE = 0x00,
	GAME_MAIN,
	GAME_OVER,
	GAME_CLEAR
};

class LudumGameState : public GameState
{
public:
	LudumGameState();
	~LudumGameState();

	void eventHandler(const SDL_Event& event);
	void update();
	void render();
private:
	enum GameStage gameStage_ = GAME_TITLE;

	Turrent* turrentList_[5];

	Turrent turrent0_;
	Turrent turrent1_;
	Turrent turrent2_;
	Turrent turrent3_;
	Turrent turrent4_;

	vector <SpaceShipBase*> spaceShipList_;
	vector <Bullet*> bulletList_;

	HPBar hpBar_;

	Sound loseLiftSound_;

	Title title_;
	GameOver gameOver_;
	GameClear gameClear_;

	Texture backgroundPic_;
	Texture backgroundPic2_;

	int spanDelay_ = 0;

	int shipDestroyCount_ = 0;

	int mousePosX_;
	int mousePosY_;

	void addNewSpaceShip_();
	void updateSpaceShips_();

	void updaetBullets_();

	bool checkCallision_(SpaceShipBase* ship, Bullet* bullet);

	void resetEntireGame_();
};

#endif /* LUDUM_GAME_STATE_H */
