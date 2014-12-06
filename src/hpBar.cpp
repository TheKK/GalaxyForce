/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: hpBar.cpp
 */

#include "hpBar.h"

HPBar::HPBar():
	hpBar_("./game/images/boss_hp_bar.png", Window::renderer())
{
	posRect_.x = 600;
	posRect_.y = 30;
	posRect_.w = 20;
	posRect_.h = 150;
}

HPBar::~HPBar()
{
}

void
HPBar::update()
{
	//SDL_assert(actor_ != nullptr);
}

void
HPBar::render()
{
	hpBar_.render(posRect_);
}

void
HPBar::bindGameActor(const GameActor& actor)
{
	actor_ = &actor;
}
