/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: userEvent.h
 */

#ifndef USER_EVENT_H
#define USER_EVENT_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <SDL2/SDL.h>

using namespace std;

enum UserEventList
{
	/* Spin serise */
	USEREVENT_SPIN_QUEST = 0x00,
	USEREVENT_SPIN_COMFIRM,
	USEREVENT_SPIN_REFUSE,

	USEREVENT_EXPLO_QUEST,
	USEREVENT_EXPLO_COMFIRM,
	USEREVENT_EXPLO_REFUSE,

	USEREVENT_COUNT
};

class UserEvent
{
	public:
		static void Init();
		static void Push(enum UserEventList);

		static vector<Uint32> ID;
};

#endif	/* USER_EVENT_H */
