/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sdlLog.cpp
 */

#include "sdlLog.h"

SDLLog::SDLLog()
{
	/* Set application log's priority to DEBUG */
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION,
			   SDL_LOG_PRIORITY_DEBUG);
}

SDLLog::~SDLLog()
{
	SDL_LogResetPriorities();
}

void
SDLLog::LogVerbose(const char* fmt, ...)
{
	va_list list;
	va_start(list, fmt);

	SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_VERBOSE,
			fmt, list);

	va_end(list);
}

void
SDLLog::LogDebug(const char* fmt, ...)
{
	va_list list;
	va_start(list, fmt);

	SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_DEBUG,
			fmt, list);

	va_end(list);
}

void
SDLLog::LogInfo(const char* fmt, ...)
{
	va_list list;
	va_start(list, fmt);

	SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_INFO,
			fmt, list);

	va_end(list);
}

void
SDLLog::LogWarn(const char* fmt, ...)
{
	va_list list;
	va_start(list, fmt);

	SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_WARN,
			fmt, list);

	va_end(list);
}

void
SDLLog::LogError(const char* fmt, ...)
{
	va_list list;
	va_start(list, fmt);

	SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_ERROR,
			fmt, list);

	va_end(list);
}

void
SDLLog::LogCritical(const char* fmt, ...)
{
	va_list list;
	va_start(list, fmt);

	SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_CRITICAL,
			fmt, list);

	va_end(list);
}
