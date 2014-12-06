/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: userEvent.cpp
 */

#include "userEvent.h"

vector<Uint32> UserEvent::ID;

void
UserEvent::Init()
{
	Uint32 id;

	ID.resize(0);

	for (int i = 0; i < USEREVENT_COUNT; i++) {
		id = SDL_RegisterEvents(1);
		if (id == (Uint32) -1)
			throw runtime_error("Can't get more user event ID");
		else
			ID.push_back(id);
	}
}

void
UserEvent::Push(enum UserEventList type)
{
	SDL_Event tmp;
	SDL_zero(tmp);
	tmp.type = ID[type];

	SDL_PushEvent(&tmp);

	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
		     "User event %d pushed", ID[type]);
}
