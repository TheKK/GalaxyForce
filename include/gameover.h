/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameover.h
 */

#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <SDL.h>

#include "window.h"
#include "texture.h"

class GameOver
{
public:
	GameOver();
	~GameOver();

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

#endif /* GAME_OVER_H */
