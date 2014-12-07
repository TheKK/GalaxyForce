/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameClear.h
 */

#ifndef GAME_CLEAR_H
#define GAME_CLEAR_H

#include <SDL.h>

#include "window.h"
#include "texture.h"

class GameClear
{
public:
	GameClear();
	~GameClear();

	void eventHandler(const SDL_Event& event);
	int update();
	void render();

	void reset();
private:
	SDL_Rect titlePosRect_ = {0};
	Texture titlePic_;

	int titleTrans_ = 0;

	bool isFadeIn_ = true;
	bool isFadeOut_ = false;
};

#endif /* GAME_CLEAR_H */
