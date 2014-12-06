
// Copyright (c) 2010 Tom Distler
//
// LICENSE: Do whatever you want. No warranty is implied or given. The code is
// released as-is... you're on your own.
//
//
#include "lua_typed_enums.h"

bool add_enum_to_lua(lua_State* L, const char* tname, ...)
{
    // NOTE: Here's the Lua code we're building and executing to define the
    //       enum.
    //
    // <tname> = setmetatable( {}, { 
    //      __index = { 
    //          <name1> = { 
    //              value = <value1>, 
    //              type = \"<tname>\"
    //          }, 
    //          ... 
    //      },
    //      __newindex = function(table, key, value)
    //          error(\"Attempt to modify read-only table\")
    //      end,
    //      __metatable = false
    // });

    va_list args;
    std::stringstream code;
    char* ename;
    int evalue;
    
    code << tname << " = setmetatable({}, {";
    code << "__index = {";

    // Iterate over the variadic arguments adding the enum values.
    va_start(args, tname);
    while ((ename = va_arg(args, char*)) != 0)
    {
        evalue = va_arg(args, int);
        code << ename << "={value=" << evalue << ",type=\"" << tname << "\"},";
    } 
    va_end(args);

    code << "},";
    code << "__newindex = function(table, key, value) error(\"Attempt to modify read-only table\") end,";
    code << "__metatable = false});";

    // Execute lua code
    if ( luaL_loadbuffer(L, code.str().c_str(), code.str().length(), 0) || lua_pcall(L, 0, 0, 0) )
    {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return false;
    }
    return true;
}

bool check_enum_type(lua_State* L, const char* tname, int index)
{
    lua_pushstring(L, "type");
    lua_gettable(L, index);
    if (!lua_isnil(L, -1))
    {
        const char* type = lua_tostring(L, -1);
        if (strcmp(type, tname) == 0)
        {
            lua_pop(L, 1);
            return true;
        }
    }
    lua_pop(L, 1);
    return false;
}

int get_enum_value(lua_State* L, int index)
{
    lua_pushstring(L, "value");
    lua_gettable(L, index);
    return luaL_checkint(L, -1);
}
