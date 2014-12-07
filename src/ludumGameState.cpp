/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: ludumGameState.cpp
 */

#include "ludumGameState.h"

LudumGameState::LudumGameState():
	loseLiftSound_("./game/sounds/loseLife.ogg"),
	backgroundPic_("./game/images/background.png", Window::renderer()),
	backgroundPic2_("./game/images/background2.png", Window::renderer())
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
	if (event.type == SDL_QUIT)
		setNext(GAME_STATE_QUIT);

	switch (gameStage_) {
	case GAME_TITLE:
		title_.eventHandler(event);
		break;

	case GAME_MAIN:
		switch (event.type) {
		case SDL_MOUSEMOTION:
			mousePosX_ = event.motion.x;
			mousePosY_ = event.motion.y;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
				if (event.key.state == SDL_PRESSED)
					for (auto e : turrentList_)
						e->shootBullet_(&bulletList_);
		}

		for (auto e : turrentList_)
			e->eventHandler(event);

		for (auto e : spaceShipList_)
			e->eventHandler(event);
		break;

	case GAME_OVER:
		gameOver_.eventHandler(event);
		break;
	case GAME_CLEAR:
		gameClear_.eventHandler(event);
		break;
	}

}

void
LudumGameState::update()
{
	for (auto e : turrentList_)
		e->update(mousePosX_, mousePosY_, &bulletList_);

	switch (gameStage_) {
	case GAME_TITLE:
		if (title_.update())
			gameStage_ = GAME_MAIN;
		break;

	case GAME_MAIN:

		updaetBullets_();
		updateSpaceShips_();

		for (auto bullet : bulletList_) {
			for (auto ship : spaceShipList_) {
				if (SDL_HasIntersection(ship->rect(),
							bullet->rect())) {
					ship->gotHit();
					bullet->suicide();
				}
			}
		}

		if (spanDelay_++ == 30) {
			addNewSpaceShip_();
			spanDelay_ = 0;
		}

		hpBar_.update();
		if (hpBar_.getLift() == 0)
			gameStage_ = GAME_OVER;

		if (shipDestroyCount_ == 70)
			gameStage_ = GAME_CLEAR;
		break;

	case GAME_OVER:
		if (gameOver_.update()) {
			resetEntireGame_();
			gameStage_ = GAME_TITLE;
		}
		break;

	case GAME_CLEAR:
		if (gameClear_.update()) {
			resetEntireGame_();
			gameStage_ = GAME_TITLE;
		}
		break;
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

	switch (gameStage_) {
	case GAME_TITLE:
		title_.render();

	case GAME_MAIN:
		hpBar_.render();
		break;

	case GAME_OVER:
		gameOver_.render();
		break;

	case GAME_CLEAR:
		gameClear_.render();
		break;
	}

	backgroundPic2_.renderFullWindow();
}

void
LudumGameState::addNewSpaceShip_()
{
	SpaceShipBase* ship;
	int startX, startY;
	int which = 0;

	if (shipDestroyCount_ < 10)
		which  = 0;
	else if (shipDestroyCount_ < 30)
		which  = rand() % 2;
	else if (shipDestroyCount_ > 40)
		which  = rand() % 3;

	switch (which) {
	case 0:
		startX = -20;
		startY = 60 + rand() % (240 - 20);
		ship = new NormalSpaceShip(startX, startY);
		break;
	case 1:
		startX = -10;
		startY = 60 + rand() % (240 - 20);
		ship = new SmallSpaceShip(startX, startY);
		break;
	case 2:
		startX = -100;
		startY = 60 + rand() % (240 - 150);
		ship = new BossSpaceShip(startX, startY);
		break;
	}

	spaceShipList_.push_back(ship);
}

void
LudumGameState::updateSpaceShips_()
{
	for (auto ship = spaceShipList_.rbegin();
	     ship != spaceShipList_.rend();
	     ship++) {

		(*ship)->update();

		if ((*ship)->rect()->x > Window::rect()->w) {
			(*ship)->suicide();
			hpBar_.removeLife();
			loseLiftSound_.Play();
		}

		if ((*ship)->isDead()) {
			delete (*ship);
			spaceShipList_.erase(std::next(ship).base());
			shipDestroyCount_++;
		}
	}

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

bool
LudumGameState::checkCallision_(SpaceShipBase* ship, Bullet* bullet)
{
	return SDL_HasIntersection(ship->rect(), bullet->rect());
}

void
LudumGameState::resetEntireGame_()
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

	title_.reset();
	gameOver_.reset();
	gameClear_.reset();
	hpBar_.resetLife();

	shipDestroyCount_ = 0;
}
