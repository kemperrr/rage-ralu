#pragma once

#include "RaluCore.hpp"
#include "NCALL.hpp"

class NCColshape : public NCEntity {
public:
	NCColshape(rage::IEntity* entryEntity);

	void Destroy();
	bool IsPointWithin(NCVector3* pos) const;
	uint8_t GetShapeType() const;
	bool operator==(NCColshape* colshape) const;

	static void Register(LuaVM* rVM);
private:
	static bool Exists(NCColshape* colshape);
	static int CreateColshapeCircle(lua_State* state);
	static int CreateColshapeSphere(lua_State* state);
	static int CreateColshapeTube(lua_State* state);
	static int CreateColshapeRectangle(lua_State* state);
	static int CreateColshapeCube(lua_State* state);
	static int GetAtColshape(lua_State* state);

	static int ForEach(lua_State* state);
	static int ToArray(lua_State* state);
	static int GetSize();
};