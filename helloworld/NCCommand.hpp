#pragma once

#include "RaluCore.hpp"
#include "NCALL.hpp"

class NCCommand {
private:

public:
	NCCommand();

	static void Register(LuaVM* rVM);
private:
	static int addCommand(lua_State* state);
};