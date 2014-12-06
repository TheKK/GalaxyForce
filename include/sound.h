/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sound.h
 */

#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alure.h>

using namespace std;

class Sound
{
	public:
		Sound();
		Sound(string filePath);
		~Sound();

		/* File operations */
		void LoadSoundFile(string filePath);

		void SetSourcePosition(ALint x, ALint y, ALint z);
		void SetSourcePosition(ALfloat x, ALfloat y, ALfloat z);

		/* Sound control */
		void Play();
		void Stop();
		void Pause();
		void Resume();

		bool hasLoaded();
		ALuint requestSource();

		/* State */
		bool IsPlaying() const;
		bool IsPaused() const;
		bool IsStopped() const;

		static bool isPlaying(ALuint source);

	private:
		ALuint source_;
		ALuint buffer_;

		void Release_();
};

#endif
