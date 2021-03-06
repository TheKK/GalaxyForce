/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: title.cpp
 */

#include "title.h"

Title::Title():
	titlePic_("./game/images/title.png", Window::renderer())
{
	titlePosRect_.x = 140;
	titlePosRect_.y = 100;
	titlePosRect_.w = 340;
	titlePosRect_.h = 210;
}

Title::~Title()
{
}

void
Title::eventHandler(const SDL_Event& event)
{
	if (isFadeIn_)
		return;

	switch (event.type) {
	case SDL_KEYDOWN:
	case SDL_MOUSEBUTTONDOWN:
		isFadeOut_ = true;
		break;
	}
}

int
Title::update()
{
	if (isFadeIn_) {
		titleTrans_ += 2;

		if (titleTrans_ > 255) {
			titleTrans_ = 255;
			isFadeIn_ = false;
		}

	}

	if (isFadeOut_) {
		titleTrans_ -= 2;

		if (titleTrans_ < 0) {
			titleTrans_ = 0;
			return 1;
		}
	}

	titlePic_.setAlpha(titleTrans_);

	return 0;
}

void
Title::render()
{
	titlePic_.render(titlePosRect_);
}

void
Title::reset()
{
	isFadeOut_ = false;
	isFadeIn_ = true;
}
