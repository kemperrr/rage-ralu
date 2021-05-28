#pragma once

#include "RaluCore.hpp"
#include "NCALL.hpp"

class NCBlip : public NCEntity {
public:
	NCBlip(rage::IEntity* entryEntity);

	void Destroy();
	float GetRadius() const;
	uint8_t GetMode() const;
	int RouteFor(lua_State* state);
	int UnrouteFor(lua_State* state);
	uint8_t GetColour() const;
	void SetColour(uint8_t colour);
	uint8_t GetAlpha() const;
	void SetAlpha(uint8_t alpha);
	float GetScale() const;
	void SetScale(float scale);
	std::string GetName() const;
	void SetName(std::string name);
	bool operator==(NCBlip* blip) const;
	

	uint16_t GetId() const;
	uint32_t GetDimension() const;
	void SetDimension(uint32_t dimension);
	NCVector3* GetPosition() const;
	void SetPosition(NCVector3* pos);
	NCVector3* GetRotation() const;
	void SetRotation(NCVector3* rot);
	uint32_t GetModel() const;
	void SetModel(uint32_t model);
	NCVector3* GetVelocity() const;
	std::string GetType() const { return strType; }

	static void Register(LuaVM* rVM);
private:
	static bool Exists(NCBlip* blip);
	static int CreateBlip(lua_State* state);
	static int CreateBlipStreamed(lua_State* state);
	static int GetAtBlip(lua_State* state);

	static int ForEach(lua_State* state);
	static int ToArray(lua_State* state);
	static int GetSize();
};