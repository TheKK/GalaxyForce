/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sprite.cpp
 */

#include "sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(const char* filePath, SDL_Renderer* renderer,
	       int w, int h,
	       Uint8 r, Uint8 g, Uint8 b)
{
	load(filePath, renderer, w, h, r, g, b);
}

Sprite::~Sprite()
{
	release_();
}

int
Sprite::load(const char* filePath, SDL_Renderer* renderer,
	     int w, int h,
	     Uint8 r, Uint8 g, Uint8 b)
{
	int sheetWidth, sheetHeight;
	SDL_Rect toBePushed;

	setRenderer(renderer);

	sheet_ = loadTexture(filePath, renderer, r, g, b);

	SDL_QueryTexture(sheet_, nullptr, nullptr, &sheetWidth, &sheetHeight);

	/* Setup clip for each frame and other stuffs*/
	totalFrame_= sheetWidth / w;

	toBePushed.y = 0;
	toBePushed.w = w;
	toBePushed.h = h;
	for (int i = 0; i <= totalFrame_; i++) {
		toBePushed.x = i * w;
		clip_.push_back(toBePushed);
	}

	return 0;
}

void
Sprite::render(const SDL_Rect& rect)
{
	SDL_assert(sheet_ != nullptr);
	SDL_assert(clip_.size() > 0);

	SDL_RenderCopyEx(targetRenderer_, sheet_, &clip_[currentFrame_], &rect,
			 0, nullptr, flip_);
}

void
Sprite::setAlpha(Uint8 value)
{
	SDL_assert(sheet_ != nullptr);

	SDL_SetTextureAlphaMod(sheet_, value);
}

void
Sprite::setFlip(enum FlipDirection dir)
{
	switch (dir) {
	case FLIP_HORIZONTAL:
		flip_ = SDL_FLIP_HORIZONTAL;
		break;
	case FLIP_VERTICAL:
		flip_ = SDL_FLIP_VERTICAL;
		break;
	case FLIP_NONE:
		flip_ = SDL_FLIP_NONE;
		break;
	}
}

void
Sprite::nextFrame()
{
	currentFrame_++;
	if (currentFrame_ == totalFrame_)
		currentFrame_ = 0;
}

void
Sprite::prevFrame()
{
	currentFrame_--;
	if (currentFrame_ < 0)
		currentFrame_ = totalFrame_ - 1;
}

void
Sprite::jumpTo(Uint16 where)
{
	SDL_assert((where >= 0) && (where < totalFrame_));

	currentFrame_ = where;
}

void
Sprite::release_()
{
	if (sheet_ != nullptr)
		SDL_DestroyTexture(sheet_);
	sheet_ = nullptr;
}
