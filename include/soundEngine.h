/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: soundEngine.h
 */

#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alure.h>

using namespace std;

class SoundEngine
{
	public:
		static void Init();
		static void Quit();
	private:
		static ALCdevice* device_;
		static ALCcontext* context_;
};

#endif
