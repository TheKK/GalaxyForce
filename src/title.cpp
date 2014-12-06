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
	switch (event.type) {
	case SDL_KEYDOWN:
	case SDL_MOUSEBUTTONDOWN:
		gameIsStart_ = true;
		break;
	}
}

int
Title::update()
{
	if (gameIsStart_) {
		titleTrans_ -= 2;

		if (titleTrans_ < 0) {
			titleTrans_ = 0;
			return 1;
		}

		titlePic_.setAlpha(titleTrans_);
	}

	return 0;
}

void
Title::render()
{
	titlePic_.render(titlePosRect_);
}
