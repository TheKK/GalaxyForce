/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameState.cpp
 */

#include "gameState.h"

GameState::~GameState()
{
}

bool
GameState::hasNext() const
{
	return (next_ != GAME_STATE_NULL);
}

enum GameStateList
GameState::next() const
{
	return next_;
}

void
GameState::setNext(enum GameStateList next)
{
	next_ = next;
}
