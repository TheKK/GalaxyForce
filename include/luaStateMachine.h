/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: luaStateMachine.h
 */

#ifndef LUA_STATE_MACHINE_H
#define LUA_STATE_MACHINE_H

#include <iostream>
#include <vector>
#include <lua.hpp>
#include <SDL.h>

#include "stateMachine.h"
#include "gameActor.h"
#include "gameActorController.h"
#include "logLocator.h"

using namespace std;

class LuaStateMachine : public StateMachine
{
public:
	LuaStateMachine();
	LuaStateMachine(const char* filePath);
	~LuaStateMachine();

	void init(const char* filePath);

	void bindActor(const GameActor& actor);
	void bindController(const GameActorController& controller);

	void onEnter();
	void onExit();
	void handleInput();
	void update();

	void setNext(char* nextState);
	bool hasNext();
	void toNext();

	/* For Lua use */
	static int lua_setNext(lua_State* L);
private:
	lua_State* states_ = nullptr;

	string currentState_ = "";
	string nextState_ = "";

	/* XXX Do I really need thiese? */
	void createNewLuaState_();
	void loadSettingScript_(const char* filePath);
};

#endif /* LUA_STATE_MACHINE_H */
