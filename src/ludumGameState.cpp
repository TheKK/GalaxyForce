/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: ludumGameState.cpp
 */

#include "ludumGameState.h"

LudumGameState::LudumGameState():
	backgroundPic_("./game/images/backbround.png", Window::renderer())
{
	Json::Value root;
	Json::Reader reader;

	turrentList_[0] = &turrent0_;
	turrentList_[1] = &turrent1_;
	turrentList_[2] = &turrent2_;
	turrentList_[3] = &turrent3_;
	turrentList_[4] = &turrent4_;

	turrentList_[0]->setRotateDegree(180);
	turrentList_[1]->setRotateDegree(180);
	turrentList_[2]->setRotateDegree(0);
	turrentList_[3]->setRotateDegree(0);
	turrentList_[4]->setRotateDegree(0);

	turrentList_[0]->setPos(180, 40);
	turrentList_[1]->setPos(420, 40);
	turrentList_[2]->setPos(100, 300);
	turrentList_[3]->setPos(260, 300);
	turrentList_[4]->setPos(500, 320);
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

	for (auto e : turrentList_)
		e->eventHandler(event);
}

void
LudumGameState::update()
{
	for (auto e : turrentList_)
		e->update(mousePosX_, mousePosY_);
}

void
LudumGameState::render()
{
	backgroundPic_.renderFullWindow();

	for (auto e : turrentList_)
		e->render();
}
