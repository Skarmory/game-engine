#ifndef lua_funcs_h
#define lua_funcs_h

#include <iostream>

#include "lua_inc.h"

int lua_print_message(lua_State* state);
int lua_create_entity_at_location(lua_State* state);

#endif