#include "lua_vm.h"

#include <Windows.h>

#include "lua_funcs.h"

using namespace std;

LuaVM::LuaVM(void)
{
	_vm = luaL_newstate();

	// Make standard libs available
	luaL_openlibs(_vm);

	// Bind functions to lua
	lua_register(_vm, "trace", lua_print_message);

	// Construct path to scripts
	char buf[256];
	GetModuleFileName(NULL, buf, 256);
	_scripts_path = string(buf).substr(0, string(buf).find_last_of("\\/")) + "\\resources\\levels\\";
}

LuaVM::~LuaVM(void)
{
	lua_close(_vm);
}

int LuaVM::call(string name)
{
	lua_getglobal(_vm, name.c_str());
	return lua_pcall(_vm, 0, 0, 0);
}

int LuaVM::load_script(string path)
{
	return luaL_dofile(_vm, (_scripts_path + path).c_str());
}