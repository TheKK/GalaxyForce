/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: numberDisplayer.cpp
 */

#include "numberDisplayer.h"

NumberDisplayer::NumberDisplayer(const char* filePath, SDL_Renderer* renderer,
				 Uint8 howManyDigitals,
				 Uint16 digitalWidth, Uint16 digitalHeight):
	numSprite_(filePath, renderer, digitalWidth, digitalHeight),
	digitalNum_(howManyDigitals)
{
	setRenderer(renderer);

	/* Set vector size and init value */
	digitalVect_.resize(digitalNum_);

	counterSetZero();
}

NumberDisplayer::~NumberDisplayer()
{
	release_();
}

void
NumberDisplayer::addNum(uint32_t value)
{
	Uint32 toNext = 0;

	digitalVect_[digitalNum_- 1] += value;
	if (digitalVect_[digitalNum_ - 1] > 9) {
		digitalVect_[digitalNum_ - 1] -= 10;
		toNext = 1;
	}

	for (Uint16 i = digitalNum_ - 2; i >= 0; i--) {
		digitalVect_[i] += toNext;

		if (digitalVect_[i] > 9) {
			toNext = 1;
			digitalVect_[i] -= 10;
		} else {
			break;
		}
	}
}

void
NumberDisplayer::setNum(int value)
{
	SDL_assert(value < pow(10, digitalNum_));
	for (int i = 0; i < digitalNum_; i++) {
		digitalVect_[i] = value / pow(10, digitalNum_ - 1 - i);
		value -= pow(10, digitalNum_ - 1 - i) * digitalVect_[i];
	}
}

uint64_t
NumberDisplayer::getNum() const
{
	Uint64 toReturn = 0;

	for (Uint16 i = 0; i < digitalVect_.size(); i++)
		toReturn +=
			(digitalVect_[i] *
			 pow(10, digitalVect_.size() - i - 1));

	return toReturn;
}

void
NumberDisplayer::setAlpha(Uint8 value)
{
	numSprite_.setAlpha(value);
}

void
NumberDisplayer::counterSetZero()
{
	for (auto& e: digitalVect_)
		e = 0;
}

void
NumberDisplayer::render(const SDL_Rect& rect)
{
	Uint16 digitalWidth = (rect.w / digitalNum_);

	for (int i = 0; i < digitalNum_; i++) {
		numSprite_.jumpTo(digitalVect_[i]);
		numSprite_.render({
				  (rect.x + digitalWidth * i), rect.y,
				  digitalWidth, rect.h
				  });
	}
}

void
NumberDisplayer::release_()
{
}
