/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameover.cpp
 */

#include "gameover.h"

GameOver::GameOver():
	titlePic_("./game/images/gameOver.png", Window::renderer())
{
	titlePosRect_.x = 140;
	titlePosRect_.y = 100;
	titlePosRect_.w = 340;
	titlePosRect_.h = 210;

	titlePic_.setAlpha(0);
}

GameOver::~GameOver()
{
}

void
GameOver::eventHandler(const SDL_Event& event)
{
}

int
GameOver::update()
{
	if (isFadeIn_) {
		titleTrans_ += 2;

		if (titleTrans_ > 255) {
			titleTrans_ = 255;
			isFadeIn_ = false;
			isFadeOut_ = true;
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
GameOver::render()
{
	titlePic_.render(titlePosRect_);
}

void
GameOver::reset()
{
	isFadeOut_ = false;
	isFadeIn_ = true;
}
