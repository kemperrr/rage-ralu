#pragma once

#include "RaluCore.hpp"
#include "NCALL.hpp"

class NCMarker : public NCEntity {
public:
	NCMarker(rage::IEntity* entryEntity);

	void Destroy();
	int GetColour(lua_State* state);
	void SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	NCVector3* GetDirection() const;
	void SetDirection(NCVector3* dir);
	float GetScale() const;
	void SetScale(float scale);
	bool IsVisible() const;
	void SetVisible(bool toggle);
	int ShowFor(lua_State* state);
	int HideFor(lua_State* state);
	bool operator==(NCMarker* checkpoint) const;

	static void Register(LuaVM* rVM);
private:
	static bool Exists(NCMarker* marker);
	static int CreateMarker(lua_State* state);
	static int GetAtMarker(lua_State* state);

	static int ForEach(lua_State* state);
	static int ToArray(lua_State* state);
	static int GetSize();
};
