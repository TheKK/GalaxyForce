/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sdlLog.h
 */

/* TODO: change a include gaurd name */
#ifndef SDL_LOG_H
#define SDL_LOG_H

#include <SDL2/SDL.h>
#include <cstdarg>

#include "log.h"

class SDLLog : public Log
{
public:
	SDLLog();
	~SDLLog();

	void LogVerbose(const char* fmt, ...);
	void LogDebug(const char* fmt, ...);
	void LogInfo(const char* fmt, ...);
	void LogWarn(const char* fmt, ...);
	void LogError(const char* fmt, ...);
	void LogCritical(const char* fmt, ...);
};

#endif 	/* SDL_LOG_H */
