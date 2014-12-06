/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: logLocator.cpp
 */

#include "logLocator.h"

Log* LogLocator::service_ = nullptr;
NullLog LogLocator::nullService_;

void
LogLocator::Init()
{
	service_ = &nullService_;
}

Log*
LogLocator::GetService()
{
	return service_;
}

void
LogLocator::Register(Log* service)
{
	if (service == nullptr)
		service_ = &nullService_;
	else
		service_ = service;
}
