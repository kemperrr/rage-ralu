#pragma once

#include "RaluCore.hpp"
#include "NCALL.hpp"

class NCObject : public NCEntity {
public:
	NCObject(rage::IEntity* entryEntity);

	void Destroy();
	bool operator==(NCObject* object) const;

	static void Register(LuaVM* rVM);
private:
	static bool Exists(NCObject* object);
	static int ForEach(lua_State* state);
	static int ToArray(lua_State* state);
	static int GetSize();

	static int CreateObject(lua_State* state);
	static int GetAtObject(lua_State* state);
};
