/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: nullLog.h
 */

#ifndef NULL_LOG_H
#define NULL_LOG_H

#include "log.h"

class NullLog : public Log
{
	public:
		void LogVerbose(const char* fmt, ...);
		void LogDebug(const char* fmt, ...);
		void LogInfo(const char* fmt, ...);
		void LogWarn(const char* fmt, ...);
		void LogError(const char* fmt, ...);
		void LogCritical(const char* fmt, ...);
};

#endif	/* NULL_LOG_H */
