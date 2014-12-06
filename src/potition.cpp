/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: position.cpp
 */

#include "position.h"

Position::Position()
{
}

Position::Position(int x, int y, int w, int h)
{
	posRect_ = {x, y, w, h};
}

Position::~Position()
{
}

void
Position::moveBy(int dx, int dy)
{
	posRect_.x += dx;
	posRect_.y += dy;
}

void
Position::moveTo(int x, int y)
{
	posRect_.x = x;
	posRect_.y = y;
}

void
Position::setX(int n)
{
	posRect_.x = n;
}

void
Position::setY(int n)
{
	posRect_.y = n;
}

void
Position::setW(int n)
{
	posRect_.w = n;
}

void
Position::setH(int n)
{
	posRect_.h = n;
}

void
Position::setRect(int x, int y, int w, int h)
{
	posRect_.x = x;
	posRect_.y = y;
	posRect_.w = w;
	posRect_.h = h;
}

int
Position::x() const
{
	return posRect_.x;
}

int
Position::y() const
{
	return posRect_.y;
}

int
Position::w() const
{
	return posRect_.w;
}

int
Position::h() const
{
	return posRect_.h;
}

const SDL_Rect&
Position::rect() const
{
	return posRect_;
}
