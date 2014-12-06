/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: timer.cpp
 */

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

class Timer
{
	public:
		Timer();
		~Timer();

		/* Timer functions */
		void Start();
		void Pause();
		void Stop();
		void Unpause();
		
		/* Return timer ticks */
		int GetTicks();

		/* Return timer status */
		bool IsPaused();
		bool IsStarted();
							
	private:
		/* The time when timer start */
		int startTicks_;

		/* The time when timer pause */
		int pauseTicks_;

		/* Show the timer status */
		bool isPaused_;
		bool isStarted_;
};

#endif	/* TIMER_H */
