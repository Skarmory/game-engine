#include "lua_funcs.h"

#include "environment.h"

using namespace std;

int lua_print_message(lua_State* state)
{
	const char* msg = lua_tostring(state, 1);
	cout << msg << endl;
	return 0;
}

int lua_create_entity_at_location(lua_State* state)
{
	string entity_id = lua_tostring(state, 1);
	int x = lua_tointeger(state, 2);
	int y = lua_tointeger(state, 3);
	int z = lua_tointeger(state, 4);

	Environment::get().get_entity_manager()->create_entity_at_loc(entity_id, x, y, z);

	return 0;
}