/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: hpBar.cpp
 */

#include "hpBar.h"

HPBar::HPBar():
	hpBar_("./game/images/lifeBar_bar.png", Window::renderer()),
	life0_("./game/images/lifeBar_life0.png", Window::renderer()),
	life1_("./game/images/lifeBar_life1.png", Window::renderer()),
	life2_("./game/images/lifeBar_life2.png", Window::renderer())
{
	posRect_.x = 60;
	posRect_.y = 5;
	posRect_.w = 70;
	posRect_.h = 35;
}

HPBar::~HPBar()
{
}

void
HPBar::update()
{
}

void
HPBar::render()
{
	hpBar_.render(posRect_);

	switch (hp_) {
	case 3:
		life2_.render(posRect_);
	case 2:
		life1_.render(posRect_);
	case 1:
		life0_.render(posRect_);
	default:
		break;
	}
}

void
HPBar::addLife()
{
	if (hp_ != 3)
		hp_++;
}

void
HPBar::removeLife()
{
	if (hp_ != 0)
		hp_--;
}

void
HPBar::resetLife()
{
	hp_ = 3;
}

int
HPBar::getLift() const
{
	return hp_;
}
