#pragma once
#include "lua.hpp"
#include <string>
#include "Resource.hpp"

class Resource;
class LuaVM {
private: 
	lua_State* r_VM;
	int r_iStackIndex;
	std::string r_strClassName;
	Resource* r_Resource;
public:
	LuaVM(Resource* resource);
	~LuaVM();

	lua_State* GetVM() { return r_VM; }
	Resource* GetResource() { return r_Resource; }
	bool LoadScript(std::string script);

	static void Panic(lua_State *lua);
};