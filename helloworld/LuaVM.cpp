#include "LuaVM.hpp"
#include <vector>
#include <iostream>
#include "Utility.hpp"


LuaVM::LuaVM(Resource* resource)
	: r_Resource(resource),
	r_iStackIndex(1)
{
	r_VM = luaL_newstate();
	luaL_openlibs(r_VM);
	//lua_atpanic(r_VM, (lua_CFunction)LuaVM::Panic);
}

LuaVM::~LuaVM() {
	lua_close(r_VM);
	r_VM = NULL;
}

void LuaVM::Panic(lua_State *lua)
{
}

auto split(const std::string& value, char separator)
-> std::vector<std::string>
{
	std::vector<std::string> result;
	std::string::size_type p = 0;
	std::string::size_type q;
	while ((q = value.find(separator, p)) != std::string::npos) {
		result.emplace_back(value, p, q - p);
		p = q + 1;
	}
	result.emplace_back(value, p);
	return result;
}

bool LuaVM::LoadScript(std::string script) {
	if (!Utility::fileExist(script.c_str())) {
		std::cout << "Error load file " << script << std::endl;
		return false;
	} else {
		if (luaL_loadfile(r_VM, script.c_str()) != 0) {
			std::cout << "Error load file " << lua_tostring(r_VM, -1) << std::endl;
			return false;
		}

		if (lua_pcall(r_VM, 0, LUA_MULTRET, 0) == 0) {
			//std::cout << "File loaded " << script << std::endl;
			return true;
		} else {
			std::string strRes = lua_tostring(r_VM, -1);

			std::vector <std::string> vecSplit;
			vecSplit = split(strRes, ':');

			if (vecSplit.size() >= 3)
			{
				std::string strFile = vecSplit[0];
				int iLine = atoi(vecSplit[1].c_str());
				std::string strMsg = vecSplit[2].substr(1);

				std::cout << "ERROR " << strFile << ":" << iLine << " " << strMsg << std::endl;
			}
			else
			{
				std::cout << "ERROR " << strRes << std::endl;
			}
		}
		return true;
	}
	return false;
}