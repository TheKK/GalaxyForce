/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: position.h
 */

#ifndef POSITION_H
#define POSITION_H

#include <SDL.h>

using namespace std;

class Position
{
public:
	Position();
	Position(int x, int y, int w, int h);
	~Position();

	void moveBy(int dx, int dy);
	void moveTo(int x, int y);

	void setX(int n);
	void setY(int n);
	void setW(int n);
	void setH(int n);
	void setRect(int x, int y, int w, int h);

	int x() const;
	int y() const;
	int w() const;
	int h() const;
	const SDL_Rect& rect() const;
private:
	SDL_Rect posRect_ = {0};
};

#endif /* POSITION_H */
