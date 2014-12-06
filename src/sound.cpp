/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sound.cpp
 */

#include "sound.h"

Sound::Sound()
{
}

Sound::Sound(string filePath)
{
	LoadSoundFile(filePath);
}

Sound::~Sound()
{
	Release_();
}

void
Sound::LoadSoundFile(string filePath)
{
	string fullPath = SDL_GetBasePath();
	fullPath += filePath;

	/* Gen buffer */
	alGenBuffers(1, &buffer_);

	/* Make a source */
	alGenSources(1, &source_);

	/* Load audio file */
	buffer_ = alureCreateBufferFromFile(fullPath.c_str());
	if (buffer_ == AL_NONE) {
		string msg("OpenAL error: file not found, ");
		msg += fullPath;
		throw runtime_error(msg);
	}

	/* Bind buffer to source */
	alSourcei(source_, AL_BUFFER, buffer_);
	if (alGetError() != AL_NO_ERROR) {
		fprintf(stderr, "AL error: %s", alureGetErrorString());
	}

}

void
Sound::SetSourcePosition(ALint x, ALint y, ALint z)
{
	alSource3i(source_, AL_POSITION, x, y, z);
}

void
Sound::SetSourcePosition(ALfloat x, ALfloat y, ALfloat z)
{
	alSource3f(source_, AL_POSITION, x, y, z);
}

void
Sound::Play()
{
	alSourcePlay(source_);
}

void
Sound::Stop()
{
	alSourceStop(source_);
}

void
Sound::Pause()
{
	alSourcePause(source_);
}

void
Sound::Resume()
{
	alSourceRewind(source_);
}

bool
Sound::hasLoaded()
{
	if (source_)
		return 1;
	else
		return 0;
}

ALuint
Sound::requestSource()
{
	ALuint source;

	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer_);
	if (alGetError() != AL_NO_ERROR) {
		fprintf(stderr, "AL error: %s", alureGetErrorString());
		return 0;
	} else
		return source;
}

bool
Sound::IsPlaying() const
{
	ALint state;
	alGetSourcei(source_, AL_SOURCE_STATE, &state);

	return (state == AL_PLAYING);
}

bool
Sound::isPlaying(ALuint source)
{
	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);

	return (state == AL_PLAYING);
}

bool
Sound::IsPaused() const
{
	ALint state;
	alGetSourcei(source_, AL_SOURCE_STATE, &state);

	return (state == AL_PAUSED);
}

bool
Sound::IsStopped() const
{
	ALint state;
	alGetSourcei(source_, AL_SOURCE_STATE, &state);

	return (state == AL_STOPPED);
}

void
Sound::Release_()
{
	alDeleteSources(1, &source_);
	alDeleteBuffers(1, &buffer_);
}

