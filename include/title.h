/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: title.h
 */

#ifndef TITLE_H
#define TITLE_H

#include <SDL.h>

#include "window.h"
#include "texture.h"

class Title
{
public:
	Title();
	~Title();

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

#endif /* TITLE_H */
