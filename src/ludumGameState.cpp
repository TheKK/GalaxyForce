/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: ludumGameState.cpp
 */

#include "ludumGameState.h"

LudumGameState::LudumGameState()
{
	Json::Value root;
	Json::Reader reader;
}

LudumGameState::~LudumGameState()
{
}

void
LudumGameState::eventHandler(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_QUIT:
		setNext(GAME_STATE_QUIT);
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_MIDDLE) {
			cout << "x, y: " << event.button.x << ":"
				<< event.button.y << endl;
		}
		break;
	case SDL_MOUSEMOTION:
		mousePosX_ = event.motion.x;
		mousePosY_ = event.motion.y;
		break;
	}
}

void
LudumGameState::update()
{
	turrent1_.update(mousePosX_, mousePosY_);
}

void
LudumGameState::render()
{
	turrent1_.render();
}
