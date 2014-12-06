/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: command.h
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

#include "gameActor.h"

using namespace std;

class Command
{
public:
	virtual ~Command() {};

	virtual void execute(GameActor& actor) = 0;
};

#endif /* COMMAND_H */
