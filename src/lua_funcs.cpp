#include "lua_funcs.h"

using namespace std;

int lua_print_message(lua_State* state)
{
	const char* msg = lua_tostring(state, 1);
	cout << msg << endl;
	return 0;
}