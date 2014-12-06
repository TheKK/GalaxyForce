/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: luaGlues.h
 */

#ifndef LUA_GLUES_H
#define LUA_GLUES_H

#include <stdexcept>
#include <lua.hpp>

#include "lua_typed_enums.h"
#include "gameActor.h"
#include "gameActorController.h"
#include "logLocator.h"

using namespace std;

class LuaGlues
{
public:
	static void register_gameActor(lua_State* L);
	static void register_gameActorController(lua_State* L);
private:
	static int gameActor_moveRight(lua_State* L);
	static int gameActor_moveLeft(lua_State* L);
	static int gameActor_jump(lua_State* L);
	static int gameActor_land(lua_State* L);
	static int gameActor_dive(lua_State* L);
	static int gameActor_normalAttack(lua_State* L);
	static int gameActor_normalAirAttack(lua_State* L);
	static int gameActor_isOnGround(lua_State* L);
	static int gameActor_setVelX(lua_State* L);
	static int gameActor_setVelY(lua_State* L);
	static int gameActor_applyAcc(lua_State* L);
	static int gameActor_setSprite(lua_State* L);

	static int gameActorController_getButtonState(lua_State* L);
	static int gameActorController_ifButtonPressed(lua_State* L);
	static int gameActorController_ifButtonReleased(lua_State* L);
};

#endif /* LUA_GLUES_H */
