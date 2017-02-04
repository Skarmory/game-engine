#include "lua_vm.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif

#include "lua_funcs.h"

using namespace std;

LuaVM::LuaVM(void)
{
	_vm = luaL_newstate();

	// Make standard libs available
	luaL_openlibs(_vm);

	// Bind functions to lua
	lua_register(_vm, "trace", lua_print_message);
	lua_register(_vm, "create_entity", lua_create_entity_at_location);

	// Construct path to scripts
	char buf[256];
	#ifdef _WIN32
	GetModuleFileName(NULL, buf, 256);
	_scripts_path = string(buf).substr(0, string(buf).find_last_of("\\/")) + "\\resources\\levels\\";
	#else
	string tmp = get_module_filename_linux();
	_scripts_path = tmp.substr(0, tmp.find_last_of("/")) + "/resources/levels/";
	#endif
}

LuaVM::~LuaVM(void)
{
	lua_close(_vm);
}

#ifndef _WIN32
std::string LuaVM::get_module_filename_linux(void) {
	char arg1[20];
        char exepath[256 + 1] = {0};

        sprintf( arg1, "/proc/%d/exe", getpid() );
        readlink( arg1, exepath, 1024 );
        return string( exepath );
}
#endif

int LuaVM::call(string name)
{
	lua_getglobal(_vm, name.c_str());
	return lua_pcall(_vm, 0, 0, 0);
}

int LuaVM::load_script(string path)
{
	return luaL_dofile(_vm, (_scripts_path + path).c_str());
}
