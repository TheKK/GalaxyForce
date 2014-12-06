/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: numberDisplayer.h
 */

#ifndef NUMBER_DISPLAYER_H
#define NUMBER_DISPLAYER_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"
#include "renderable.h"

using namespace std;

class NumberDisplayer : public Renderable
{
public:
	NumberDisplayer(const char* filePath, SDL_Renderer* renderer,
			Uint8 howManyDigitals,
			Uint16 digitalWidth, Uint16 digitalHeight);
	~NumberDisplayer();

	void render(const SDL_Rect& rect);

	void addNum(Uint32 value);
	void setNum(int value);
	Uint64 getNum() const;

	void setAlpha(Uint8 value);

	void counterSetZero();
private:
	Sprite numSprite_;

	vector<Uint8> digitalVect_;
	Uint16 digitalNum_;

	void release_();
};

#endif	/* NUMBER_DISPLAYER_H */
