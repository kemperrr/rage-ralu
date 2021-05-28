#pragma once

#include "RaluCore.hpp"
#include "NCEntity.hpp"

class NCCheckpoint : public NCEntity {
public:
	NCCheckpoint(rage::IEntity* entryEntity);

	bool Destroy() const;
	int GetColour(lua_State* state);
	void SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	NCVector3* GetDirection() const;
	void SetDirection(NCVector3* pos);
	float GetRadius() const;
	void SetRadius(float radius);
	bool IsVisible() const;
	void SetVisible(bool toggle);
	int ShowFor(lua_State* state);
	int HideFor(lua_State* state);
	bool operator==(NCCheckpoint* checkpoint) const;


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
	uint8_t GetAlpha() const;
	void SetAlpha(uint8_t alpha);
	std::string GetType() const { return strType; }


	static void Register(LuaVM* rVM);
private:
	static bool Exists(NCCheckpoint* checkpoint);
	static int CreateCheckpoint(lua_State* state);
	static int GetAtCheckpoint(lua_State* state);

	static int ForEach(lua_State* state);
	static int ToArray(lua_State* state);
	static int GetSize();
};