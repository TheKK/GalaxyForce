/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: luaGlues.cpp
 */

#include "luaGlues.h"

#define lua_table_begine(lua_State) \
	lua_newtable(lua_State)

#define lua_table_end(lua_State, tableName) \
	lua_setglobal(lua_State, tableName)

#define lua_table_add_function(lua_State, fieldName, cfunctionName) \
	do { \
		lua_pushcfunction(lua_State, cfunctionName); \
		lua_setfield(lua_State, -2, fieldName); \
	} while (0)

#define lua_getglobal_safe(lua_State, name) \
	do { \
		lua_getglobal(L, name); \
		if (lua_isnil(L, -1)) { \
			LogLocator::GetService()->LogError( \
			    "[LuaGlues] Global variable %s not exist", #name); \
			throw runtime_error("Lua error, program shutdown"); \
		} \
	} while (0)

void
LuaGlues::register_gameActor(lua_State* L)
{
	SDL_assert(L != nullptr);

	/* Glues for class GameActor */
	lua_table_begine(L);
	lua_table_add_function(L, "moveRight", gameActor_moveRight);
	lua_table_add_function(L, "moveLeft", gameActor_moveLeft);
	lua_table_add_function(L, "jump", gameActor_jump);
	lua_table_add_function(L, "isOnGround", gameActor_isOnGround);
	lua_table_add_function(L, "setVelY", gameActor_setVelY);
	lua_table_add_function(L, "setVelX", gameActor_setVelX);
	lua_table_add_function(L, "applyAcc", gameActor_applyAcc);
	lua_table_add_function(L, "setSprite", gameActor_setSprite);
	lua_table_add_function(L, "normalAttack", gameActor_normalAttack);
	lua_table_end(L, "GameActor");

	add_enum_to_lua(L, "Sprites",
			"ON_GROUND", SPRITE_ON_GROUND,
			"JUMPING", SPRITE_JUMPING,
			"DIVE", SPRITE_DIVE,
			"NORMAL_ATTACK", SPRITE_NORMAL_ATTACK,
			0);
}

void
LuaGlues::register_gameActorController(lua_State* L)
{
	SDL_assert(L != nullptr);

	lua_table_begine(L);
	lua_table_add_function(L, "getButtonState",
			       gameActorController_getButtonState);
	lua_table_add_function(L, "ifButtonPressed",
			       gameActorController_ifButtonPressed);
	lua_table_add_function(L, "ifButtonReleased",
			       gameActorController_ifButtonReleased);
	lua_table_end(L, "Controller");

	add_enum_to_lua(L, "Buttons",
			"JUMP", BUTTON_JUMP,
			"NORMAL_ATTACK", BUTTON_NORMAL_ATTACK,
			"SPECIAL_ATTACK" ,BUTTON_SPECIAL_ATTACK,
			"EVADE", BUTTON_EVADE,
			"UP", BUTTON_UP,
			"DOWN", BUTTON_DOWN,
			"RIGHT", BUTTON_RIGHT,
			"LEFT", BUTTON_LEFT,
			0);
}

int
LuaGlues::gameActor_moveRight(lua_State* L)
{
	void* actorPtr = nullptr;

	/* Check number of arguments */
	if (lua_gettop(L) > 0)
		return luaL_error(L, "This function doesn't need arguments");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	((GameActor*) actorPtr)->moveRight();

	return 0;
}

int
LuaGlues::gameActor_moveLeft(lua_State* L)
{
	void* actorPtr = nullptr;

	/* Check number of arguments */
	if (lua_gettop(L) > 0)
		return luaL_error(L, "This function doesn't need arguments");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	((GameActor*) actorPtr)->moveLeft();

	return 0;
}

int
LuaGlues::gameActor_jump(lua_State* L)
{
	void* actorPtr = nullptr;

	/* Check number of arguments */
	if (lua_gettop(L) > 0)
		return luaL_error(L, "This function doesn't need arguments");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	((GameActor*) actorPtr)->jump();

	return 0;
}

int
LuaGlues::gameActor_isOnGround(lua_State* L)
{
	void* actorPtr = nullptr;

	/* Check number of arguments */
	if (lua_gettop(L) > 0)
		return luaL_error(L, "This function doesn't need arguments");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	lua_pushboolean(L, ((GameActor*) actorPtr)->isOnGround());

	return 1;
}

int
LuaGlues::gameActor_setVelX(lua_State* L)
{
	void* actorPtr = nullptr;
	int value;

	/* Check number of arguments */
	if (lua_gettop(L) < 1)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 1)
		return luaL_error(L, "Too much argument");

	/* Check type of argument */
	if (!lua_isnumber(L, 1))
		return luaL_error(L, "First argument is not number");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	value = lua_tonumber(L, 1);

	((GameActor*) actorPtr)->setVelX(value);

	return 0;
}

int
LuaGlues::gameActor_setVelY(lua_State* L)
{
	void* actorPtr = nullptr;
	int value;

	/* Check number of arguments */
	if (lua_gettop(L) < 1)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 1)
		return luaL_error(L, "Too much argument");

	/* Check type of argument */
	if (!lua_isnumber(L, 1))
		return luaL_error(L, "First argument is not number");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	value = lua_tonumber(L, 1);

	((GameActor*) actorPtr)->setVelY(value);

	return 0;
}

int
LuaGlues::gameActor_applyAcc(lua_State* L)
{
	void* actorPtr = nullptr;
	int dx, dy;

	/* Check number of arguments */
	if (lua_gettop(L) < 2)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 2)
		return luaL_error(L, "Too much argument");

	/* Check type of argument */
	if (!lua_isnumber(L, 1))
		return luaL_error(L, "First argument is not number");
	if (!lua_isnumber(L, 2))
		return luaL_error(L, "Second argument is not number");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	dx = lua_tonumber(L, 1);
	dy = lua_tonumber(L, 2);

	((GameActor*) actorPtr)->applyAcc(dx, dy);

	return 0;
}

int
LuaGlues::gameActor_setSprite(lua_State* L)
{
	void* actorPtr = nullptr;
	enum ActorSprite sprite;

	/* Check number of arguments */
	if (lua_gettop(L) < 1)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 1)
		return luaL_error(L, "Too much argument");

	/* Check type of argument */
	if (!check_enum_type(L, "Sprites", 1))
		return luaL_error(L, "Second argument is not enum Sprites");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	sprite = (enum ActorSprite) get_enum_value(L, 1);

	((GameActor*) actorPtr)->setSprite(sprite);

	return 0;
}

int
LuaGlues::gameActor_dive(lua_State* L)
{
	return 0;
}

int
LuaGlues::gameActor_normalAttack(lua_State* L)
{
	void* actorPtr = nullptr;

	/* Check number of arguments */
	if (lua_gettop(L) < 0)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 0)
		return luaL_error(L, "Too much argument");

	lua_getglobal_safe(L, "gameActor");
	actorPtr = lua_touserdata(L, -1);

	((GameActor*) actorPtr)->normalAttack();

	return 0;
}

int
LuaGlues::gameActor_normalAirAttack(lua_State* L)
{
	return 0;
}

int
LuaGlues::gameActorController_getButtonState(lua_State* L)
{
	void* controllerPtr = nullptr;
	enum Buttons button;

	/* Check number of arguments */
	if (lua_gettop(L) < 1)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 1)
		return luaL_error(L, "Too much argument");

	/* Check type of argument */
	if (!check_enum_type(L, "Buttons", 1))
		return luaL_error(L, "First argument is not enum Button");

	lua_getglobal_safe(L, "controller");
	controllerPtr = lua_touserdata(L, -1);

	button = (enum Buttons) get_enum_value(L, 1);

	if (((GameActorController*) controllerPtr)->getButtonState(button))
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);

	return 1;
}

int
LuaGlues::gameActorController_ifButtonPressed(lua_State* L)
{
	void* controllerPtr = nullptr;
	enum Buttons button;

	/* Check number of arguments */
	if (lua_gettop(L) < 1)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 1)
		return luaL_error(L, "Too much argument");

	/* Check type of argument */
	if (!check_enum_type(L, "Buttons", 1))
		return luaL_error(L, "First argument is not enum Button");

	lua_getglobal_safe(L, "controller");
	controllerPtr = lua_touserdata(L, -1);

	button = (enum Buttons) get_enum_value(L, 1);

	if(((GameActorController*) controllerPtr)->ifButtonPressed(button))
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);

	return 1;
}

int
LuaGlues::gameActorController_ifButtonReleased(lua_State* L)
{
	void* controllerPtr = nullptr;
	enum Buttons button;

	/* Check number of arguments */
	if (lua_gettop(L) < 1)
		return luaL_error(L, "Too few argument");
	else if (lua_gettop(L) > 1)
		return luaL_error(L, "Too much argument");

	/* Check type of argument */
	if (!check_enum_type(L, "Buttons", 1))
		return luaL_error(L, "First argument is not enum Button");

	lua_getglobal_safe(L, "controller");
	controllerPtr = lua_touserdata(L, -1);

	button = (enum Buttons) get_enum_value(L, 1);

	if(((GameActorController*) controllerPtr)->ifButtonReleased(button))
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);

	return 1;
}
