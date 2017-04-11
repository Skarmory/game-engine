#ifndef lua_vm_h
#define lua_vm_h

#include <string>
#include "lua_inc.h"

class LuaVM
{
public:
	explicit LuaVM(void);
	~LuaVM(void);

	int call(const std::string& name);
	int load_script(const std::string& path);

private:
	lua_State* _vm;
	std::string _scripts_path;

#ifndef _WIN32
	std::string get_module_filename_linux(void);
#endif
};

#endif
