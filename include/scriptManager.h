/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: scriptManager.h
 */

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <lua.hpp>

using namespace std;

class ScriptManager
{
	public:
		ScriptManager(){};
		~ScriptManager(){};

		static void NewState(char* filePath);
		static void CloseState();

		static void LoadFile(char* filePath);

		static int GetGlobalInteger(char* variableName);
		static const char* GetGlobalString(char* variableName);

		static int GetGlobalInt(string script, string variable);

		static lua_State* L;
};

#endif
