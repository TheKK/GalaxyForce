/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameState.h
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>

enum GameStateList
{
	GAME_STATE_NULL = 0x00,

	GAME_STATE_INTRO,
	GAME_STATE_MAIN,

	GAME_STATE_TEST,

	GAME_STATE_QUIT
};

class GameState
{
public:
	virtual ~GameState();

	virtual void eventHandler(const SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	bool hasNext() const;
	enum GameStateList next() const;
protected:
	void setNext(enum GameStateList next);
private:
	enum GameStateList next_ = GAME_STATE_NULL;
};

#endif	/* GAME_STATE_H */
