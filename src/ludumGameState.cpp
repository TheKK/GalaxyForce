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

	turrentList_[0]->setRotateDegree(90);
	turrentList_[1]->setRotateDegree(90);
	turrentList_[2]->setRotateDegree(-90);
	turrentList_[3]->setRotateDegree(-90);
	turrentList_[4]->setRotateDegree(-90);

	turrentList_[0]->setPos(180, 20);
	turrentList_[1]->setPos(420, 20);
	turrentList_[2]->setPos(100, 320);
	turrentList_[3]->setPos(260, 320);
	turrentList_[4]->setPos(500, 320);
}

LudumGameState::~LudumGameState()
{
	for (auto e : spaceShipList_) {
		delete e;
		e = nullptr;
	}
	spaceShipList_.clear();

	for (auto e : bulletList_) {
		delete e;
		e = nullptr;
	}
	bulletList_.clear();
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
		if (event.button.button == SDL_BUTTON_RIGHT)
			addNewSpaceShip_();
		break;
	case SDL_MOUSEMOTION:
		mousePosX_ = event.motion.x;
		mousePosY_ = event.motion.y;
		break;
	}

	for (auto e : turrentList_)
		e->eventHandler(event);

	for (auto e : spaceShipList_)
		e->eventHandler(event);
}

void
LudumGameState::update()
{
	for (auto e : turrentList_)
		e->update(mousePosX_, mousePosY_, &bulletList_);

	updaetBullets_();
	updateSpaceShips_();

	for (auto bullet : bulletList_) {
		for (auto ship : spaceShipList_) {
			if (SDL_HasIntersection(ship->rect(), bullet->rect())) {
				ship->suicide();
				bullet->suicide();
			}
		}
	}
}

void
LudumGameState::render()
{
	backgroundPic_.renderFullWindow();

	for (auto e : bulletList_)
		e->render();

	for (auto e : turrentList_)
		e->render();

	for (auto e : spaceShipList_)
		e->render();
}

void
LudumGameState::addNewSpaceShip_()
{
	SpaceShipBase* ship;
	int startX, startY;

	startX = 20;
	startY = rand() % Window::height();

	ship = (SpaceShipBase*) new NormalSpaceShip(startX, startY);

	spaceShipList_.push_back(ship);
}

void
LudumGameState::updateSpaceShips_()
{
	for (auto ship = spaceShipList_.rbegin();
	     ship != spaceShipList_.rend();
	     ship++) {

		(*ship)->update();

		if ((*ship)->isDead()) {
			delete (*ship);
			spaceShipList_.erase(std::next(ship).base());
		}
	}
}

bool
LudumGameState::checkCallision_(SpaceShipBase* ship, Bullet* bullet)
{
	return SDL_HasIntersection(ship->rect(), bullet->rect());
}


void
LudumGameState::updaetBullets_()
{
	for (auto bullet = bulletList_.rbegin();
	     bullet != bulletList_.rend();
	     bullet++) {

		(*bullet)->update();

		if ((*bullet)->isDead()) {
			delete (*bullet);
			bulletList_.erase(std::next(bullet).base());
		}
	}
}
