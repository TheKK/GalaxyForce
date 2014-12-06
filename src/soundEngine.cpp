/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: soundEngine.cpp
 */

#include "soundEngine.h"

ALCdevice* SoundEngine::device_ = nullptr;
ALCcontext* SoundEngine::context_ = nullptr;

void
SoundEngine::Init()
{
	ALuint major, minor;

	device_ = alcOpenDevice(nullptr);
	if (device_ == nullptr) {
		string msg("OpenAL error: ");
		msg += alcGetError(device_);
		throw runtime_error(msg);
	}

	context_ = alcCreateContext(device_, nullptr);
	if (context_ == nullptr || alcMakeContextCurrent(context_) == ALC_FALSE) {
		if (context_ == nullptr)
			alcDestroyContext(context_);
		alcCloseDevice(device_);

		string msg("OpenAL error: ");
		msg += alcGetError(device_);
		throw runtime_error(msg);
	}

	alListener3i(AL_POSITION, 0, 0, 0);

	SDL_Log("OpenAL opened %s.\n",
		alcGetString(device_, ALC_DEVICE_SPECIFIER));

	alureGetVersion(&major, &minor);
	SDL_Log("Used ALURE version %d.%d.\n", major, minor);
}

void
SoundEngine::Quit()
{
	alcMakeContextCurrent(nullptr);

	alcDestroyContext(context_);
	context_ = nullptr;

	alcCloseDevice(device_);
	device_ = nullptr;
}
