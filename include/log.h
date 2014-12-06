/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: log.h
 */

#ifndef LOG_H
#define LOG_H

class Log
{
public:
	virtual ~Log() {};

	virtual void LogVerbose(const char* fmt, ...) = 0;
	virtual void LogDebug(const char* fmt, ...) = 0;
	virtual void LogInfo(const char* fmt, ...) = 0;
	virtual void LogWarn(const char* fmt, ...) = 0;
	virtual void LogError(const char* fmt, ...) = 0;
	virtual void LogCritical(const char* fmt, ...) = 0;
};

#endif	/* LOG_H */
