/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: luaStateMachine.cpp
 */

#include "luaStateMachine.h"

#include "luaGlues.h"

LuaStateMachine::LuaStateMachine()
{
}

LuaStateMachine::LuaStateMachine(const char* filePath)
{
	init(filePath);
}

LuaStateMachine::~LuaStateMachine()
{
	if (states_)
		lua_close(states_);
	states_ = nullptr;
}

void
LuaStateMachine::init(const char* filePath)
{
	createNewLuaState_();

	loadSettingScript_(filePath);

	/* Register needed functions */
	LuaGlues::register_gameActor(states_);
	LuaGlues::register_gameActorController(states_);

	lua_newtable(states_);
	lua_pushcfunction(states_, lua_setNext);
	lua_setfield(states_, -2, "setNext");
	lua_setglobal(states_, "StateMachine");

	/* Set 'this' address as Lua global variable */
	lua_pushlightuserdata(states_, (void*) this);
	lua_setglobal(states_, "FSM");

	/* Init machine state */
	setNext((char*) "onGround");
	toNext();
}

void
LuaStateMachine::bindActor(const GameActor& actor)
{
	lua_pushlightuserdata(states_, (void*) &actor);
	lua_setglobal(states_, "gameActor");
}

void
LuaStateMachine::bindController(const GameActorController& controller)
{
	lua_pushlightuserdata(states_, (void*) &controller);
	lua_setglobal(states_, "controller");
}

void
LuaStateMachine::onEnter()
{
	lua_pushstring(states_, (char*) "onEnter");
	lua_gettable(states_, -2);

	/* Push argument */
	if (lua_pcall(states_, 0, 0, 0) != LUA_OK) {
		LogLocator::GetService()->LogError(
			"[LuaStateMachine] onEnter: Lua error %s",
			lua_tostring(states_, -1));
		lua_pop(states_, 1);
		throw runtime_error("Lua error, program shutdown");
	}
}

void
LuaStateMachine::onExit()
{
	lua_pushstring(states_, (char*) "onExit");
	lua_gettable(states_, -2);

	/* Push argument */
	if (lua_pcall(states_, 0, 0, 0) != LUA_OK) {
		LogLocator::GetService()->LogError(
			"[LuaStateMachine] onExit: Lua error %s",
			lua_tostring(states_, -1));
		lua_pop(states_, 1);
		throw runtime_error("Lua error, program shutdown");
	}
}

void
LuaStateMachine::handleInput()
{
	lua_pushstring(states_, (char*) "handleInput");
	lua_gettable(states_, -2);

	/* Push argument */
	if (lua_pcall(states_, 0, 0, 0) != LUA_OK) {
		LogLocator::GetService()->LogError(
			"[LuaStateMachine] handleInput: Lua error %s",
			lua_tostring(states_, -1));
		lua_pop(states_, 1);
		throw runtime_error("Lua error, program shutdown");
	}
}

void
LuaStateMachine::update()
{
	lua_pushstring(states_, (char*) "update");
	lua_gettable(states_, -2);

	/* Push argument */
	if (lua_pcall(states_, 0, 0, 0) != LUA_OK) {
		LogLocator::GetService()->LogError(
			"[LuaStateMachine] update: Lua error %s",
			lua_tostring(states_, -1));
		lua_pop(states_, 1);
		throw runtime_error("Lua error, program shutdown");
	}

	/* See if need to change to new state */
	if (hasNext()) {
		onExit();
		toNext();
		onEnter();
	}
}

void
LuaStateMachine::toNext()
{
	SDL_assert(nextState_ != "");

	currentState_ = nextState_;
	nextState_ = "";

	/* Make sure nothing go wrong and pop them all */
	if (lua_gettop(states_) > 1)
		LogLocator::GetService()->LogWarn(
			"[LuaStateMachine] Lua stack height is not 1");
	lua_pop(states_, lua_gettop(states_));

	/* Get new table and check error */
	lua_getglobal(states_, currentState_.c_str());
	if (lua_isnil(states_, -1)) {
		LogLocator::GetService()->LogCritical(
			"[LuaStateMachine] State \"%s\" does not exist",
			currentState_.c_str());
		throw runtime_error("Critical error, program shutdown");

	} else if (!lua_istable(states_, -1)) {
		LogLocator::GetService()->LogCritical(
			"[LuaStateMachine] State \"%s\" is not a table",
			currentState_.c_str());
		throw runtime_error("Critical error, program shutdown");
	}
}

void
LuaStateMachine::setNext(char* state)
{
	nextState_ = state;
};

bool
LuaStateMachine::hasNext()
{
	return (nextState_ != "");
}

int
LuaStateMachine::lua_setNext(lua_State* L)
{
	void* LuaStateMachinePtr = nullptr;
	char* nextState = nullptr;

	/* Check number of argument(s) */
	if (lua_gettop(L) < 1)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 1)
		return luaL_error(L, "Too much argument");

	/* Check argument type */
	if (!lua_isstring(L, 1))
		return luaL_error(L, "First argument is not string");

	lua_getglobal(L, "FSM");
	LuaStateMachinePtr = (void*) lua_topointer(L, -1);
	nextState = (char*) lua_tostring(L, 1);

	((LuaStateMachine*) LuaStateMachinePtr)->setNext(nextState);

	return 0;
}

void
LuaStateMachine::createNewLuaState_()
{
	states_ = luaL_newstate();
	if (states_ == nullptr) {
		LogLocator::GetService()->LogCritical(
			"[LuaStateMachine]"
			"No enough memory to create Lua state");
		throw runtime_error("Critical error, program shutdown");
	}

	luaL_openlibs(states_);
}

void
LuaStateMachine::loadSettingScript_(const char* filePath)
{
	string fullPath;

	fullPath = SDL_GetBasePath();
	fullPath += filePath;

	if (luaL_dofile(states_, fullPath.c_str()) != LUA_OK) {
		LogLocator::GetService()->LogError(
			"[LuaStateMachine] Lua error %s",
			lua_tostring(states_, -1));
		lua_pop(states_, 1);
		throw runtime_error("Lua script error, program shutdown");
	}
}

