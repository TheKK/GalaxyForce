/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: waveTitle.h
 */

#ifndef WAVE_TITLE_H
#define WAVE_TITLE_H

#include <SDL.h>

#include "window.h"
#include "texture.h"

class WaveTitle
{
public:
	WaveTitle();
	~WaveTitle();

	void eventHandler(const SDL_Event& event);
	void update();
	void render();
private:
	Texture titlePic_;
	SDL_Rect titlePosRect_ = {0};

	int blinkDelay_ = 0;
};

#endif /* WAVE_TITLE_H */
